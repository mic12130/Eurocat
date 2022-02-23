#pragma once

#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/profile/TrackProfile.h"
#include "screen/ScreenWrapper.h"
#include "screen/GraphicsWrapper.h"

namespace Eurocat::Hmi::Track
{
	class IVelRenderer
	{
	public:
		virtual ~IVelRenderer() = default;
		virtual void Render(
			IRadarTargetDataProvider& rt,
			const TrackProfile& profile,
			Gdiplus::Color color,
			int minutes,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		) = 0;
	};
}
