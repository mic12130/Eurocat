#pragma once

#include "plugin/input/PopupMenuItem.h"
#include "plugin/input/PopupMenuDelegate.h"
#include "hmi/track/action/ITrackActionHandler.h"

namespace Eurocat::Hmi::Track
{
	class RunwayActionHandler : public ITrackActionHandler, public Plugin::Input::PopupMenuDelegate
	{
	public:
		void OnTriggerAction(
			const TrackProfile& trackProfile,
			Screen::ScreenWrapper& screen,
			Screen::MouseButton button,
			POINT point, RECT area
		) override;
		void OnSelectItem(Plugin::Input::PopupMenuItem item, POINT point, RECT rect) override;

	private:
		std::vector<CString> GetActiveArrivalRunways(CString icao);
		CString callsignForPopup;
		CString destForPopup;
	};
}
