#include "base/pch.h"

#include "tagitem/CflFunction.h"

#include "common/unit/AltitudeConverter.h"
#include "plugin/PluginEnvironment.h"
#include "plugin/FlightPlanHelper.h"
#include "window/LevelPopupMenu.h"

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
		auto fp = PluginEnvironment::Shared().GetPlugin().FlightPlanSelectASEL();

		if (!FlightPlanHelper::IsWritable(fp))
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

	void CflFunction::OnSelectLevel(int level, Hmi::Unit::UnitDisplayMode unit)
	{
		auto fp = PluginEnvironment::Shared().GetPlugin().FlightPlanSelect(callsignForPopup);
		int levelToSet = level;

		if (unit == UnitDisplayMode::Metric)
		{
			levelToSet = AltitudeConverter::MeterToFeet(levelToSet);
		}

		fp.GetControllerAssignedData().SetClearedAltitude(levelToSet);
	}
}
