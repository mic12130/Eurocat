#include "base/pch.h"

#include "hmi/track/action/LabelDataActionHandler.h"

#include "plugin/input/PopupEdit.h"
#include "plugin/extension/FlightPlanExtension.h"
#include "plugin/PluginAccess.h"

using namespace Eurocat::Common;
using namespace Eurocat::Plugin;
using namespace Eurocat::Plugin::Input;

namespace Eurocat::Hmi::Track
{
	void LabelDataActionHandler::OnTriggerAction(const TrackProfile& trackProfile, Screen::ScreenWrapper& screen, Screen::MouseButton button, POINT point, RECT area)
	{
		if (button == Screen::MouseButton::Left)
		{
			auto fp = PluginAccess::Shared().GetPlugin().FlightPlanSelect(trackProfile.flightPlanId.value());
			auto fpExtension = FlightPlanExtension(fp);

			if (!fpExtension.GetWritable())
			{
				return;
			}

			CString labelData = fpExtension.GetOpDataText();
			auto popupEdit = std::make_shared<PopupEdit>(labelData, true);
			popupEdit->delegate = shared_from_this();
			popupEdit->Show(point, area);

			flightPlanCallsignForPopupEdit = trackProfile.flightPlanId.value();
		}
	}

	void LabelDataActionHandler::OnSubmit(CString str, POINT point, RECT rect)
	{
		auto fp = PluginAccess::Shared().GetPlugin().FlightPlanSelect(flightPlanCallsignForPopupEdit);
		FlightPlanExtension(fp).SetOpDataText(str);
	}
}
