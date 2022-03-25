#pragma once

#include "hmi/unit/UnitDisplayManager.h"
#include "hmi/track/action/ITrackActionHandler.h"
#include "window/LevelPopupMenuDelegate.h"

namespace Eurocat::Hmi::Track
{
	class CflActionHandler : public ITrackActionHandler, public Window::LevelPopupMenuDelegate
	{
	public:
		CflActionHandler(Hmi::Unit::UnitDisplayManager& unitDisplayManager);
		void OnTriggerAction(
			const TrackProfile& trackProfile,
			Screen::ScreenWrapper& screen,
			Screen::MouseButton button,
			POINT point, RECT area
		) override;
		void OnSelectLevel(std::optional<int> level, Hmi::Unit::UnitDisplayMode unit) override;

	private:
		Hmi::Unit::UnitDisplayManager& unitDisplayManager;
		CString callsignForPopup;
	};
}
