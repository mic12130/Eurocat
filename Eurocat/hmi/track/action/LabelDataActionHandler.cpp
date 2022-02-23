#include "base/pch.h"

#include "hmi/track/action/LabelDataActionHandler.h"

#include "plugin/input/PopupEdit.h"
#include "common/OpData.h"
#include "plugin/PluginEnvironment.h"
#include "plugin/FlightPlanHelper.h"

using namespace Eurocat::Common;
using namespace Eurocat::Plugin;
using namespace Eurocat::Plugin::Input;

namespace Eurocat::Hmi::Track
{
	void LabelDataActionHandler::OnTriggerAction(const TrackProfile& trackProfile, Screen::ScreenWrapper& screen, Screen::MouseButton button, POINT point, RECT area)
	{
		if (button == Screen::MouseButton::Left)
		{
			auto fp = PluginEnvironment::Shared().GetPlugin().FlightPlanSelect(trackProfile.flightPlanId.value());

			if (!FlightPlanHelper::IsWritable(fp))
			{
				return;
			}

			CString labelData = OpData::GetForFlightPlan(fp);
			auto popupEdit = std::make_shared<PopupEdit>(labelData, true);
			popupEdit->delegate = shared_from_this();
			popupEdit->Show(point, area);

			flightPlanCallsignForPopupEdit = trackProfile.flightPlanId.value();
		}
	}

	void LabelDataActionHandler::OnSubmit(CString str, POINT point, RECT rect)
	{
		auto fp = PluginEnvironment::Shared().GetPlugin().FlightPlanSelect(flightPlanCallsignForPopupEdit);
		OpData::SetForFlightPlan(fp, str);
	}
}
