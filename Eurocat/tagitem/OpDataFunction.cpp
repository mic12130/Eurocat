#include "base/pch.h"

#include "tagitem/OpDataFunction.h"

#include "common/OpData.h"
#include "plugin/input/PopupEdit.h"
#include "system/SystemManager.h"
#include "plugin/FlightPlanHelper.h"

using namespace Eurocat::Common;
using namespace Eurocat::Plugin::Input;
using namespace Eurocat::Plugin;

namespace Eurocat::TagItem
{
	void OpDataFunction::OnFunctionCall(int functionId, CString itemString, POINT point, RECT area)
	{
		auto fp = SystemManager::Shared().GetPlugin().FlightPlanSelectASEL();

		if (!FlightPlanHelper::IsWritable(fp))
		{
			return;
		}

		CString str = OpData::GetForFlightPlan(fp);

		auto popupEdit = std::make_shared<PopupEdit>(str, true);
		popupEdit->delegate = shared_from_this();
		popupEdit->Show(point, area);

		flightPlanCallsignForPopup = fp.GetCallsign();
	}

	void OpDataFunction::OnSubmit(CString str, POINT point, RECT rect)
	{
		auto fp = SystemManager::Shared().GetPlugin().FlightPlanSelect(flightPlanCallsignForPopup);
		OpData::SetForFlightPlan(fp, str);
	}
}
