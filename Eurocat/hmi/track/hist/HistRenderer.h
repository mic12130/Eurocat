#pragma once

#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/hist/IHistRenderer.h"

namespace Eurocat::Hmi::Track
{
	class HistRenderer : public IHistRenderer
	{
	public:
		void Render(std::vector<Common::Coordinate> positions, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics) override;
	};
}
