#include "base/pch.h"

#include "hmi/track/hist/HistRenderController.h"

#include "hmi/track/hist/HistRenderer.h"

namespace Eurocat::Hmi::Track
{
	HistRenderController::HistRenderController()
		: HistRenderController(std::make_shared<HistRenderer>())
	{
	}

	HistRenderController::HistRenderController(std::shared_ptr<IHistRenderer> renderer) : renderer(std::move(renderer))
	{
	}

	void HistRenderController::OnRenderSsrTrack(IRadarTargetDataProvider& rt, const OptionData& option, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		if (option.enableHistoryDotsDisplay)
		{
			renderer->Render(rt.GetHistoricalPositions(option.historyDotsCount), color, screen, graphics);
		}
	}
}
