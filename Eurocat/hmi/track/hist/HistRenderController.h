#pragma once

#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/option/OptionData.h"
#include "hmi/track/hist/IHistRenderer.h"

namespace Eurocat::Hmi::Track
{
	class HistRenderController
	{
	public:
		HistRenderController();
		HistRenderController(std::shared_ptr<IHistRenderer> renderer);
		void OnRenderSsrTrack(
			IRadarTargetDataProvider& rt,
			const OptionData& option,
			Gdiplus::Color color,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		);

	private:
		std::shared_ptr<IHistRenderer> renderer;
	};
}
