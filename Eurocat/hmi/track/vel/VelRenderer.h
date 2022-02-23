#pragma once

#include "hmi/track/vel/IVelRenderer.h"

namespace Eurocat::Hmi::Track
{
	class VelRenderer : public IVelRenderer
	{
	public:
		void Render(
			IRadarTargetDataProvider& rt,
			const TrackProfile& profile,
			Gdiplus::Color color,
			int minutes,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		) override;
	};
}
