#include "base/pch.h"

#include "tagitem/OpDataFunction.h"

#include "plugin/input/PopupEdit.h"
#include "plugin/extension/FlightPlanExtension.h"
#include "system/SystemManager.h"

using namespace Eurocat::Common;
using namespace Eurocat::Plugin::Input;
using namespace Eurocat::Plugin;

namespace Eurocat::TagItem
{
	void OpDataFunction::OnFunctionCall(int functionId, CString itemString, POINT point, RECT area)
	{
		auto fp = SystemManager::Shared().GetPlugin().FlightPlanSelectASEL();
		auto fpExt = FlightPlanExtension(fp);

		if (!fpExt.GetWritable())
		{
			return;
		}

		CString str = fpExt.GetOpDataText();

		auto popupEdit = std::make_shared<PopupEdit>(str, true);
		popupEdit->delegate = shared_from_this();
		popupEdit->Show(point, area);

		flightPlanCallsignForPopup = fp.GetCallsign();
	}

	void OpDataFunction::OnSubmit(CString str, POINT point, RECT rect)
	{
		auto fp = SystemManager::Shared().GetPlugin().FlightPlanSelect(flightPlanCallsignForPopup);
		auto fpExt = FlightPlanExtension(fp);
		fpExt.SetOpDataText(str);
	}
}
