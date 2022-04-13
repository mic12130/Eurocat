#include "base/pch.h"

#include "hmi/track/TrackManager.h"

#include "hmi/track/TrackColor.h"
#include "hmi/track/FlightPlanDataProvider.h"
#include "hmi/track/RadarTargetDataProvider.h"
#include "hmi/track/TrackObjectId.h"
#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/AltitudeFilter.h"
#include "hmi/track/tag/TagRenderController.h"
#include "hmi/track/tag/RepositionHelper.h"
#include "hmi/track/vel/VelRenderController.h"
#include "hmi/track/hist/HistRenderController.h"
#include "hmi/track/symbol/SymbolRenderController.h"
#include "hmi/track/symbol/SymbolObjectInfoFactory.h"
#include "hmi/track/action/SymbolActionHandler.h"
#include "hmi/track/action/AcidActionHandler.h"
#include "hmi/track/action/CflActionHandler.h"
#include "hmi/track/action/GroundSpeedActionHandler.h"
#include "hmi/track/action/DestActionHandler.h"
#include "hmi/track/action/LabelDataActionHandler.h"
#include "hmi/track/action/RunwayActionHandler.h"
#include "hmi/track/tag/render_data/CoupledTrackTagData.h"
#include "hmi/track/tag/render_data/FlightPlanTrackTagData.h"
#include "hmi/track/tag/render_data/UncoupledTrackTagData.h"
#include "hmi/FlightPlanDisplayStateGenerator.h"
#include "screen/ScreenObjectType.h"
#include "plugin/PluginEnvironment.h"
#include "hmi/cursor/CursorManager.h"

using namespace Eurocat::Plugin::Extension;
using namespace Eurocat::Plugin;
using namespace Eurocat::Screen;
using namespace Eurocat::Hmi::Cursor;
using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	TrackManager::TrackManager(Unit::UnitDisplayManager& unitDisplayManager)
		: unitDisplayManager(unitDisplayManager)
	{
		actionHandlerMap = {
			{ TrackObjectIdSuffix::kSymbol, std::make_shared<SymbolActionHandler>(trackProfileManager, repositioningProfileId) },
			{ TrackObjectIdSuffix::kAcidLabel, std::make_shared<AcidActionHandler>(trackProfileManager, option) },
			{ TrackObjectIdSuffix::kCflLabel, std::make_shared<CflActionHandler>(unitDisplayManager) },
			{ TrackObjectIdSuffix::kGroundSpeedLabel, std::make_shared<GroundSpeedActionHandler>(trackProfileManager, option) },
			{ TrackObjectIdSuffix::kDestLabel, std::make_shared<DestActionHandler>() },
			{ TrackObjectIdSuffix::kLabelDataLabel, std::make_shared<LabelDataActionHandler>() },
			{ TrackObjectIdSuffix::kRunwayLabel, std::make_shared<RunwayActionHandler>() }
		};
	}

	void TrackManager::OnRender(Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		auto& plugin = PluginEnvironment::Shared().GetPlugin();
		auto radarArea = screen.GetRadarArea();
		std::vector<RenderableTrack> renderableTracks;

		// We will only look for flight plan tracks when FPASD enabled
		if (option.showFlightPlanTracks)
		{
			for (auto fp = plugin.FlightPlanSelectFirst(); fp.IsValid(); fp = plugin.FlightPlanSelectNext(fp))
			{
				if (!fp.IsValid())
				{
					continue;
				}

				if (auto px = screen.ConvertCoordFromPositionToPixel(fp.GetFPTrackPosition().GetPosition());
					InRange(px, radarArea) == false)
				{
					continue;
				}

				if (fp.GetFPState() == EuroScopePlugIn::FLIGHT_PLAN_STATE_SIMULATED &&
					fp.GetCorrelatedRadarTarget().IsValid() == false)
				{
					// FP Track
					auto& fpAttribute = PluginEnvironment::Shared().AttributeForFlightPlan(fp);
					auto fpData = std::make_shared<FlightPlanDataProvider>(fp, fpAttribute);
					renderableTracks.emplace_back(fp.GetCallsign(), RenderableTrack::Type::FlightPlanTrack, fpData, nullptr);
				}
			}
		}

		for (auto rt = plugin.RadarTargetSelectFirst(); rt.IsValid(); rt = plugin.RadarTargetSelectNext(rt))
		{
			if (!rt.IsValid())
			{
				continue;
			}

			if (auto px = screen.ConvertCoordFromPositionToPixel(rt.GetPosition().GetPosition());
				InRange(px, radarArea) == false)
			{
				continue;
			}
			
			auto rtData = std::make_shared<RadarTargetDataProvider>(rt);

			if (rt.GetPosition().GetReportedGS() < kGroundTrafficMaxSpeed)
			{
				// Ground traffic
				renderableTracks.emplace_back(rt.GetCallsign(), RenderableTrack::Type::Ground, nullptr, rtData);
			}
			else
			{
				if (rt.GetPosition().GetTransponderC())
				{
					// SSR
					if (auto coupledFp = rt.GetCorrelatedFlightPlan(); coupledFp.IsValid())
					{
						// Coupled
						auto& fpAttribute = PluginEnvironment::Shared().AttributeForFlightPlan(coupledFp);
						auto fpData = std::make_shared<FlightPlanDataProvider>(coupledFp, fpAttribute);

						renderableTracks.emplace_back(rt.GetCallsign(), RenderableTrack::Type::Coupled, fpData, rtData);
					}
					else
					{
						// Uncoupled
						renderableTracks.emplace_back(rt.GetCallsign(), RenderableTrack::Type::Uncoupled, nullptr, rtData);
					}
				}
				else
				{
					// PSR
					renderableTracks.emplace_back(rt.GetCallsign(), RenderableTrack::Type::Primary, nullptr, rtData);
				}
			}
		}

		std::sort(renderableTracks.begin(), renderableTracks.end());
		RenderTracks(renderableTracks, screen, graphics);
	}

	void TrackManager::OnOverScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args)
	{
	}

	void TrackManager::OnClickScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args)
	{
		if (args.objectType != ScreenObjectType::kTrack)
		{
			return;
		}

		if (args.objectId == TrackObjectId::kNoActionObjectId)
		{
			return;
		}

		if (args.objectId == TrackObjectId::kRepositioningBackgroundObjectId)
		{
			if (repositioningProfileId.has_value())
			{
				EuroScopePlugIn::CPosition coord;
				TrackProfile profile;

				if (trackProfileManager.TryGetProfile(repositioningProfileId.value(), profile) == false)
				{
					throw std::runtime_error("Profile not found");
				}

				if (profile.trackType == TrackProfile::TrackType::FlightPlan)
				{
					coord = PluginEnvironment::Shared().GetPlugin().FlightPlanSelect(profile.flightPlanId.value()).GetFPTrackPosition().GetPosition();
				}
				else if (profile.trackType == TrackProfile::TrackType::Coupled || profile.trackType == TrackProfile::TrackType::Uncoupled)
				{
					coord = PluginEnvironment::Shared().GetPlugin().RadarTargetSelect(profile.radarTargetId.value()).GetPosition().GetPosition();
				}

				CPoint cursorPx;
				GetCursorPos(&cursorPx);

				CPoint targetPx = screen.ConvertCoordFromPositionToPixel(coord);
				CPoint closestPolarPx = RepositionHelper::GetClosestPolarPx(targetPx, cursorPx);

				profile.isTagRepositioning = false;
				profile.tagOffsetX = closestPolarPx.x - targetPx.x;
				profile.tagOffsetY = closestPolarPx.y - targetPx.y;
				trackProfileManager.TryUpdateProfile(profile);
			}
			else
			{
				throw std::runtime_error("Repositioning background exists, but repositioningProfileId is null");
			}

			repositioningProfileId = std::nullopt;
			CursorManager::shared->SetCursorType(CursorType::Normal);

			return;
		}

		auto objectIdExtraction = TrackObjectId::Extract(args.objectId);
		TrackProfile trackProfile;

		trackProfileManager.TryGetProfile(objectIdExtraction.trackProfileId, trackProfile);
		actionHandlerMap[objectIdExtraction.suffix]->OnTriggerAction(trackProfile, screen, args.mouseButton, args.point, args.rect);
	}

	void TrackManager::OnMoveScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args)
	{
	}

	OptionData& TrackManager::GetOption()
	{
		return option;
	}

	TrackProfileManager& TrackManager::GetTrackProfileManager()
	{
		return trackProfileManager;
	}

	void TrackManager::RenderTracks(std::vector<RenderableTrack>& tracks, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		// Render controllers of track components
		auto altitudeFilter = std::make_shared<AltitudeFilter>(option);
		SymbolRenderController symbolRenderController(screen, graphics);
		TagRenderController tagRenderController(altitudeFilter);
		VelRenderController velRenderController;
		HistRenderController histRenderController;
		SymbolObjectInfoFactory symbolObjectInfoFactory;

		for (auto& track : tracks)
		{
			if (track.type == RenderableTrack::Type::Ground)
			{
				auto& rt = *track.rt;
				CString callsign = rt.GetTargetId();
				auto color = TrackColor::GetGroundTrackColor();
				auto symbolObjectInfo = symbolObjectInfoFactory.MakeForGroundTrack();

				symbolRenderController.OnRenderGroundTrack(rt, color, symbolObjectInfo);
			}
			else if (track.type == RenderableTrack::Type::Primary)
			{
				if (option.hidePsrSymbol == false)
				{
					auto& rt = *track.rt;
					auto color = TrackColor::GetPsrTrackColor();
					auto symbolObjectInfo = symbolObjectInfoFactory.MakeForPsrTrack();

					symbolRenderController.OnRenderPsrTrack(rt, color, option, symbolObjectInfo);
				}
			}
			else if (track.type == RenderableTrack::Type::Uncoupled)
			{
				auto& rt = *track.rt;
				auto profile = trackProfileManager.GetOrCreateProfileForUncoupledTrack(rt.GetTargetId());
				auto unit = GetUnit(rt);
				auto tagData = UncoupledTrackTagData(rt, profile, option, unit);
				auto color = TrackColor::GetUncoupledTrackColor(profile.isIql);
				bool isSelected = IsSelected(rt);
				auto symbolObjectInfo = symbolObjectInfoFactory.MakeForUncoupledTrack(profile);

				symbolRenderController.OnRenderSsrTrack(rt, color, option, isSelected, symbolObjectInfo);
				tagRenderController.OnRenderUncoupledTrack(rt, tagData, color, screen, graphics);
				velRenderController.OnRenderSsrTrack(rt, profile, option, color, screen, graphics);
				histRenderController.OnRenderSsrTrack(rt, option, color, screen, graphics);
			}
			else if (track.type == RenderableTrack::Type::Coupled)
			{
				auto& fp = *track.fp;
				auto& rt = *track.rt;
				auto profile = trackProfileManager.GetOrCreateProfileForCoupledTrack(fp.GetCallsign(), rt.GetTargetId());
				auto unit = GetUnit(rt);
				auto tagData = CoupledTrackTagData(rt, fp, profile, option, unit);
				auto color = TrackColor::GetTrackColor(fp, profile.isIql);
				bool isSelected = IsSelected(fp);
				auto symbolObjectInfo = symbolObjectInfoFactory.MakeForCoupledTrack(fp, profile);

				symbolRenderController.OnRenderSsrTrack(rt, color, option, isSelected, symbolObjectInfo);
				tagRenderController.OnRenderCoupledTrack(rt, tagData, color, screen, graphics);
				velRenderController.OnRenderSsrTrack(rt, profile, option, color, screen, graphics);
				histRenderController.OnRenderSsrTrack(rt, option, color, screen, graphics);
			}
			else if (track.type == RenderableTrack::Type::FlightPlanTrack)
			{
				auto& fp = *track.fp;
				auto& rt = *track.rt;
				auto profile = trackProfileManager.GetOrCreateProfileForFlightPlanTrack(fp.GetCallsign());
				auto unit = GetUnit(fp);
				auto tagData = FlightPlanTrackTagData(fp, profile, option, unit);
				auto color = TrackColor::GetTrackColor(fp, profile.isIql);
				bool isSelected = IsSelected(fp);
				auto symbolObjectInfo = symbolObjectInfoFactory.MakeForFlightPlanTrack(fp, profile);

				symbolRenderController.OnRenderFlightPlanTrack(fp, color, isSelected, symbolObjectInfo);
				tagRenderController.OnRenderFlightPlanTrack(tagData, color, screen, graphics);
			}
		}
	}

	bool TrackManager::InRange(POINT px, RECT rect)
	{
		return px.x > rect.left && px.x < rect.right&& px.y > rect.top && px.y < rect.bottom;
	}

	bool TrackManager::IsSelected(IRadarTargetDataProvider& rt)
	{
		return PluginEnvironment::Shared().GetPlugin().RadarTargetSelectASEL().GetSystemID() == rt.GetTargetId();
	}

	bool TrackManager::IsSelected(IFlightPlanDataProvider& fp)
	{
		return PluginEnvironment::Shared().GetPlugin().FlightPlanSelectASEL().GetCallsign() == fp.GetCallsign();
	}

	bool TrackManager::IsAboveTransAltitude(IRadarTargetDataProvider& rt)
	{
		int level = rt.GetPressureAltitude();

		if (level > PluginEnvironment::Shared().GetPlugin().GetTransitionAltitude())
		{
			level = rt.GetFlightLevel();
		}

		return level > PluginEnvironment::Shared().GetPlugin().GetTransitionAltitude();
	}

	auto TrackManager::GetUnit(IRadarTargetDataProvider& rt) -> Hmi::Unit::UnitDisplayMode
	{
		return unitDisplayManager.GetUnitForRadarTarget(rt.GetTargetId());
	}

	auto TrackManager::GetUnit(IFlightPlanDataProvider& fp) -> Hmi::Unit::UnitDisplayMode
	{
		return unitDisplayManager.GetUnitForRadarTarget(fp.GetCallsign());
	}
}
