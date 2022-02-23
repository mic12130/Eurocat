#pragma once

#include "base/pch.h"

#include "screen/ScreenWrapper.h"
#include "screen/MouseButton.h"
#include "hmi/track/profile/TrackProfile.h"

namespace Eurocat::Hmi::Track
{
	class ITrackActionHandler
	{
	public:
		virtual ~ITrackActionHandler() = default;
		virtual void OnTriggerAction(const TrackProfile& trackProfile, Screen::ScreenWrapper& screen, Screen::MouseButton button, POINT point, RECT area) = 0;
	};
}
