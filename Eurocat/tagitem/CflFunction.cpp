#include "base/pch.h"

#include "tagitem/CflFunction.h"

#include "common/unit/AltitudeConverter.h"
#include "system/SystemManager.h"
#include "window/LevelPopupMenu.h"
#include "plugin/extension/FlightPlanExtension.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;
using namespace Eurocat::Window;

namespace Eurocat::TagItem
{
	CflFunction::CflFunction(Hmi::Unit::UnitDisplayManager& unitDisplayManager) : unitDisplayManager(unitDisplayManager)
	{
	}

	void CflFunction::OnFunctionCall(int functionId, CString itemString, POINT point, RECT area)
	{
		auto fp = SystemManager::Shared().GetPlugin().FlightPlanSelectASEL();
		auto fpExt = FlightPlanExtension(fp);

		if (!fpExt.GetWritable())
		{
			return;
		}

		int currentCfl = fp.GetControllerAssignedData().GetClearedAltitude();
		auto unit = unitDisplayManager.GetUnitForFlightPlan(fp.GetCallsign());

		if (unit == UnitDisplayMode::Metric)
		{
			currentCfl = AltitudeConverter::FeetToMeter(currentCfl);
		}

		auto popupMenu = std::make_shared<LevelPopupMenu>(currentCfl, unit);
		popupMenu->levelPopupDelegate = shared_from_this();
		popupMenu->Show(point, area);
		callsignForPopup = fp.GetCallsign();
	}

	void CflFunction::OnSelectLevel(std::optional<int> level, Hmi::Unit::UnitDisplayMode unit)
	{
		auto fp = SystemManager::Shared().GetPlugin().FlightPlanSelect(callsignForPopup);
		auto fpExt = FlightPlanExtension(fp);
		auto levelToSet = level;

		if (unit == UnitDisplayMode::Metric && level.has_value())
		{
			levelToSet = AltitudeConverter::MeterToFeet(level.value());
		}

		fpExt.SetCfl(levelToSet);
	}
}
