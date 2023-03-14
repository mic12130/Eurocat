#include "base/pch.h"

#include "hmi/track/action/CflActionHandler.h"

#include "window/LevelPopupMenu.h"
#include "common/unit/AltitudeConverter.h"
#include "system/SystemContainer.h"
#include "plugin/extension/FlightPlanExtension.h"

using namespace Eurocat::Window;
using namespace Eurocat::Hmi::Unit;
using namespace Eurocat::Plugin;
using namespace Eurocat::Screen;
using namespace Eurocat::Common::Unit;

namespace Eurocat::Hmi::Track
{
	CflActionHandler::CflActionHandler(Hmi::Unit::UnitDisplayManager& unitDisplayManager) : unitDisplayManager(unitDisplayManager)
	{
	}

	void CflActionHandler::OnTriggerAction(const TrackProfile& trackProfile, Screen::ScreenWrapper& screen, Screen::MouseButton button, POINT point, RECT area)
	{
		if (button == MouseButton::Left)
		{
			auto fp = SystemContainer::Shared().GetPlugin()
				.FlightPlanSelect(trackProfile.flightPlanId.value());
			auto fpExtension = FlightPlanExtension(fp);

			if (!fpExtension.GetWritable())
			{
				return;
			}

			int selectedFeets = fp.GetControllerAssignedData().GetClearedAltitude();
			callsignForPopup = trackProfile.flightPlanId.value();
			UnitDisplayMode unit;

			if (trackProfile.trackType == TrackProfile::TrackType::Coupled ||
				trackProfile.trackType == TrackProfile::TrackType::Uncoupled)
			{
				unit = unitDisplayManager.GetUnitForRadarTarget(trackProfile.radarTargetId.value());
			}
			else
			{
				unit = unitDisplayManager.GetUnitForFlightPlan(trackProfile.flightPlanId.value());
			}

			if (unit == UnitDisplayMode::Imperial)
			{
				auto popup = std::make_shared<LevelPopupMenu>(selectedFeets, UnitDisplayMode::Imperial);
				popup->levelPopupDelegate = shared_from_this();
				popup->Show(point, area);
			}
			else if (unit == UnitDisplayMode::Metric)
			{
				int selectedMeters = AltitudeConverter::FeetToMeter(selectedFeets);
				auto popup = std::make_shared<LevelPopupMenu>(selectedMeters, UnitDisplayMode::Metric);
				popup->levelPopupDelegate = shared_from_this();
				popup->Show(point, area);
			}
		}
		else if (button == MouseButton::Middle)
		{
			auto fp = SystemContainer::Shared().GetPlugin().FlightPlanSelect(trackProfile.flightPlanId.value());
			auto fpExtension = FlightPlanExtension(fp);
			fpExtension.SetCflAcknowledged(!fpExtension.GetCflAcknowledged());
		}
	}

	void CflActionHandler::OnSelectLevel(std::optional<int> level, Hmi::Unit::UnitDisplayMode unit)
	{
		auto levelToSet = level;

		if (unit == UnitDisplayMode::Metric && level.has_value())
		{
			levelToSet = AltitudeConverter::MeterToFeet(level.value());
		}

		if (auto fp = SystemContainer::Shared().GetPlugin().FlightPlanSelect(callsignForPopup);
			fp.IsValid())
		{
			FlightPlanExtension(fp).SetCfl(levelToSet);
		}
	}
}
