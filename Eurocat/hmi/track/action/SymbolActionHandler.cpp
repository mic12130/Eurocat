#include "base/pch.h"

#include "hmi/track/action/SymbolActionHandler.h"

#include "hmi/cursor/CursorManager.h"
#include "system/SystemManager.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Screen;
using namespace Eurocat::Hmi::Cursor;
using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	SymbolActionHandler::SymbolActionHandler(
		TrackProfileManager& trackProfileManager, 
		std::optional<CString>& repositioningProfileId)
		: trackProfileManager(trackProfileManager),
		repositioningProfileId(repositioningProfileId)
	{
	}

	void SymbolActionHandler::OnTriggerAction(
		const TrackProfile& trackProfile,
		Screen::ScreenWrapper& screen,
		Screen::MouseButton button,
		POINT point, RECT area)
	{
		auto& plugin = SystemManager::Shared().GetPlugin();

		if (button == MouseButton::Left)
		{
			// Callsign is always required to fire a ES function, so we will
			// fetch one when it is a radar target
			if (trackProfile.trackType == TrackProfile::TrackType::Uncoupled)
			{
				for (auto rt = plugin.RadarTargetSelectFirst();
					rt.IsValid();
					rt = plugin.RadarTargetSelectNext(rt))
				{
					if (rt.GetSystemID() == trackProfile.radarTargetId.value())
					{
						plugin.SetASELAircraft(rt);
						break;
					}
				}
			}
			else
			{
				// Coupled or flight plan track - both have correlated flight plan
				plugin.SetASELAircraft(plugin.FlightPlanSelect(trackProfile.flightPlanId.value()));
			}
		}
		else if (button == MouseButton::Middle)
		{
			auto updatedTrackProfile(trackProfile);
			updatedTrackProfile.isIql = !updatedTrackProfile.isIql;
			trackProfileManager.TryUpdateProfile(updatedTrackProfile);
		}
		else if (button == MouseButton::Right)
		{
			TrackProfile updatedTrackProfile(trackProfile);
			updatedTrackProfile.isTagRepositioning = true;

			trackProfileManager.TryUpdateProfile(updatedTrackProfile);
			repositioningProfileId = updatedTrackProfile.id;
			CursorManager::shared->SetCursorType(CursorType::Interactive);
		}
	}
}
