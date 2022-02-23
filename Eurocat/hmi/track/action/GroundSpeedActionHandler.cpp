#include "base/pch.h"

#include "hmi/track/action/GroundSpeedActionHandler.h"

using namespace Eurocat::Screen;
using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	GroundSpeedActionHandler::GroundSpeedActionHandler(TrackProfileManager& trackProfileManager, OptionData& option)
		: trackProfileManager(trackProfileManager), option(option)
	{
	}

	void GroundSpeedActionHandler::OnTriggerAction(
		const TrackProfile& trackProfile,
		Screen::ScreenWrapper& screen,
		Screen::MouseButton button,
		POINT point, RECT area)
	{
		if (button == MouseButton::Left)
		{
			if (option.enableVelocityVectorDisplay)
			{
				TrackProfile updatedTrackProfile(trackProfile);
				updatedTrackProfile.userSetVel = trackProfile.userSetVel.value_or(true) ?
					std::make_optional(false) : std::nullopt;

				trackProfileManager.TryUpdateProfile(updatedTrackProfile);
			}
			else
			{
				TrackProfile updatedTrackProfile(trackProfile);
				updatedTrackProfile.userSetVel = trackProfile.userSetVel.value_or(false) ?
					std::nullopt : std::make_optional(true);

				trackProfileManager.TryUpdateProfile(updatedTrackProfile);
			}
		}
	}
}
