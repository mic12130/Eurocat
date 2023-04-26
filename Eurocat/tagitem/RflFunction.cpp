#include "base/pch.h"

#include "tagitem/RflFunction.h"

#include "common/unit/AltitudeConverter.h"
#include "plugin/extension/FlightPlanExtension.h"
#include "plugin/PluginAccess.h"
#include "window/LevelPopupMenu.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;
using namespace Eurocat::Window;

namespace Eurocat::TagItem
{
	RflFunction::RflFunction(Hmi::Unit::UnitDisplayManager& unitDisplayManager) : unitDisplayManager(unitDisplayManager)
	{
	}

	void RflFunction::OnFunctionCall(int functionId, CString itemString, POINT point, RECT area)
	{
		auto fp = PluginAccess::Shared().GetPlugin().FlightPlanSelectASEL();
		auto fpExt = FlightPlanExtension(fp);

		if (!fpExt.GetWritable())
		{
			return;
		}

		int currentRfl = fp.GetFinalAltitude();
		auto unit = unitDisplayManager.GetUnitForFlightPlan(fp.GetCallsign());

		if (unit == UnitDisplayMode::Metric)
		{
			currentRfl = AltitudeConverter::FeetToMeter(currentRfl);
		}

		auto popupMenu = std::make_shared<LevelPopupMenu>(currentRfl, unit);
		popupMenu->levelPopupDelegate = shared_from_this();
		popupMenu->Show(point, area);
		callsignForPopup = fp.GetCallsign();
	}

	void RflFunction::OnSelectLevel(std::optional<int> level, Hmi::Unit::UnitDisplayMode unit)
	{
		auto fp = PluginAccess::Shared().GetPlugin().FlightPlanSelect(callsignForPopup);
		int levelToSet = level.value_or(0); // Convert NONE selection to 0 as RFL cannot be none

		if (unit == UnitDisplayMode::Metric)
		{
			levelToSet = kRflMeterToFeetMap[levelToSet];
		}

		fp.GetControllerAssignedData().SetFinalAltitude(levelToSet);
	}
}
