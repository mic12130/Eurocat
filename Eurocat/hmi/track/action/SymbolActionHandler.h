#pragma once

#include "hmi/track/action/ITrackActionHandler.h"
#include "hmi/track/profile/TrackProfileManager.h"

namespace Eurocat::Hmi::Track
{
	class SymbolActionHandler : public ITrackActionHandler
	{
	public:
		SymbolActionHandler(TrackProfileManager& trackProfileManager);
		void OnTriggerAction(
			const TrackProfile& trackProfile,
			Screen::ScreenWrapper& screen,
			Screen::MouseButton button,
			POINT point, RECT area
		) override;

	private:
		TrackProfileManager& trackProfileManager;
	};
}
