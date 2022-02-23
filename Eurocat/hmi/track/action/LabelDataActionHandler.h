#pragma once

#include "hmi/track/action/ITrackActionHandler.h"
#include "plugin/input/PopupEditDelegate.h"

namespace Eurocat::Hmi::Track
{
	class LabelDataActionHandler : public ITrackActionHandler, public Plugin::Input::PopupEditDelegate
	{
	public:
		void OnTriggerAction(
			const TrackProfile& trackProfile,
			Screen::ScreenWrapper& screen,
			Screen::MouseButton button,
			POINT point, RECT area
		) override;
		void OnSubmit(CString str, POINT point, RECT rect) override;

	private:
		CString flightPlanCallsignForPopupEdit;
	};
}
