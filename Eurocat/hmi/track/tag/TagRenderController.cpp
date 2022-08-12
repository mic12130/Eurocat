#include "base/pch.h"

#include "hmi/track/tag/TagRenderController.h"

#include "system/SystemManager.h"
#include "hmi/track/AltitudeFilter.h"
#include "hmi/track/tag/TagRenderer.h"

using namespace Eurocat::Hmi::Track;
using namespace Eurocat::Common;
using namespace Eurocat::Plugin;

namespace Eurocat::Hmi::Track
{
	TagRenderController::TagRenderController(std::shared_ptr<IAltitudeFilter> altitudeFilter)
		: TagRenderController(std::make_shared<TagRenderer>(), std::move(altitudeFilter))
	{
	}

	TagRenderController::TagRenderController(
		std::shared_ptr<ITagRenderer> renderer,
		std::shared_ptr<IAltitudeFilter> altitudeFilter)
		: renderer(std::move(renderer)),
		altitudeFilter(std::move(altitudeFilter))
	{
	}

	void TagRenderController::OnRenderCoupledTrack(
		IRadarTargetDataProvider& rt, 
		ITagDataProvider& tagData, 
		Gdiplus::Color color, 
		Screen::ScreenWrapper& screen, 
		Screen::GraphicsWrapper& graphics)
	{
		if (altitudeFilter->InRange(rt, SystemManager::Shared().GetPlugin()) == false &&
			tagData.CanOverrideFilter() == false)
		{
			return;
		}

		renderer->RenderTagLabels(
			tagData,
			color,
			screen,
			graphics
		);
	}

	void TagRenderController::OnRenderUncoupledTrack(
		IRadarTargetDataProvider& rt, 
		ITagDataProvider& tagData, 
		Gdiplus::Color color, 
		Screen::ScreenWrapper& screen,
		Screen::GraphicsWrapper& graphics)
	{
		if (altitudeFilter->InRange(rt, SystemManager::Shared().GetPlugin()) == false &&
			tagData.CanOverrideFilter() == false)
		{
			return;
		}

		renderer->RenderTagLabels(
			tagData,
			color,
			screen,
			graphics
		);
	}

	void TagRenderController::OnRenderFlightPlanTrack(
		ITagDataProvider& tagData, 
		Gdiplus::Color color, 
		Screen::ScreenWrapper& screen, 
		Screen::GraphicsWrapper& graphics)
	{
		renderer->RenderTagLabels(
			tagData,
			color,
			screen,
			graphics
		);
	}
}
