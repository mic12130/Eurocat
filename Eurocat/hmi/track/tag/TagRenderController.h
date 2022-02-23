#pragma once

#include "hmi/track/option/OptionData.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/tag/ITagRenderer.h"
#include "hmi/track/IAltitudeFilter.h"
#include "hmi/track/tag/render_data/ITagDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class TagRenderController
	{
	public:
		TagRenderController(std::shared_ptr<IAltitudeFilter> altitudeFilter);
		TagRenderController(
			std::shared_ptr<ITagRenderer> renderer,
			std::shared_ptr<IAltitudeFilter> altitudeFilter
		);
		void OnRenderCoupledTrack(
			IRadarTargetDataProvider& rt,
			ITagDataProvider& tagData,
			Gdiplus::Color color,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		);
		void OnRenderUncoupledTrack(
			IRadarTargetDataProvider& rt,
			ITagDataProvider& tagData,
			Gdiplus::Color color,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		);
		void OnRenderFlightPlanTrack(
			ITagDataProvider& tagData,
			Gdiplus::Color color,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		);

	private:
		std::shared_ptr<ITagRenderer> renderer;
		std::shared_ptr<IAltitudeFilter> altitudeFilter;
	};
}
