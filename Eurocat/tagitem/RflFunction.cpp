#include "base/pch.h"

#include "tagitem/RflFunction.h"

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
	RflFunction::RflFunction(Hmi::Unit::UnitDisplayManager& unitDisplayManager) : unitDisplayManager(unitDisplayManager)
	{
	}

	void RflFunction::OnFunctionCall(int functionId, CString itemString, POINT point, RECT area)
	{
		auto fp = PluginEnvironment::Shared().GetPlugin().FlightPlanSelectASEL();

		if (!FlightPlanHelper::IsWritable(fp))
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

	void RflFunction::OnSelectLevel(int level, Hmi::Unit::UnitDisplayMode unit)
	{
		auto fp = PluginEnvironment::Shared().GetPlugin().FlightPlanSelect(callsignForPopup);
		int levelToSet = level;

		if (unit == UnitDisplayMode::Metric)
		{
			levelToSet = kRflMeterToFeetMap[levelToSet];
		}

		fp.GetControllerAssignedData().SetFinalAltitude(levelToSet);
	}
}