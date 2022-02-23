#pragma once

#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/option/OptionData.h"
#include "hmi/track/vel/IVelRenderer.h"

namespace Eurocat::Hmi::Track
{
	class VelRenderController
	{
	public:
		VelRenderController();
		VelRenderController(std::shared_ptr<IVelRenderer> renderer);
		void OnRenderSsrTrack(
			IRadarTargetDataProvider& rt,
			const TrackProfile& profile,
			const OptionData& option,
			Gdiplus::Color color,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		);

	private:
		std::shared_ptr<IVelRenderer> renderer;
	};
}
