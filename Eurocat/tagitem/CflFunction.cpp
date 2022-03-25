#include "base/pch.h"

#include "tagitem/CflFunction.h"

#include "common/unit/AltitudeConverter.h"
#include "plugin/PluginEnvironment.h"
#include "plugin/FlightPlanHelper.h"
#include "window/LevelPopupMenu.h"
#include "plugin/extension/CflData.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Plugin::Extension;
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

	void CflFunction::OnSelectLevel(std::optional<int> level, Hmi::Unit::UnitDisplayMode unit)
	{
		auto fp = PluginEnvironment::Shared().GetPlugin().FlightPlanSelect(callsignForPopup);
		auto levelToSet = level;

		if (unit == UnitDisplayMode::Metric && level.has_value())
		{
			levelToSet = AltitudeConverter::MeterToFeet(level.value());
		}

		CflData::SetForFlightPlan(fp, levelToSet);
	}
}
