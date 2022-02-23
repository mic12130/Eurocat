#pragma once

#include "hmi/track/option/OptionData.h"
#include "hmi/track/action/ITrackActionHandler.h"
#include "hmi/track/profile/TrackProfileManager.h"

namespace Eurocat::Hmi::Track
{
	class AcidActionHandler : public ITrackActionHandler
	{
	public:
		AcidActionHandler(
			TrackProfileManager& trackProfileManager,
			OptionData& option
		);
		void OnTriggerAction(
			const TrackProfile& trackProfile,
			Screen::ScreenWrapper& screen,
			Screen::MouseButton button,
			POINT point, RECT area
		) override;

	private:
		TrackProfileManager& trackProfileManager;
		OptionData& option;
	};
}
