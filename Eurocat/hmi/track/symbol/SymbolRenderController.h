#pragma once

#include "hmi/track/symbol/ISymbolRenderer.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/IFlashHelper.h"
#include "hmi/track/option/OptionData.h"

namespace Eurocat::Hmi::Track
{
	class SymbolRenderController
	{
	public:
		SymbolRenderController(Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics);
		SymbolRenderController(std::shared_ptr<ISymbolRenderer> renderer, std::shared_ptr<IFlashHelper> flashHelper);
		void OnRenderSsrTrack(
			IRadarTargetDataProvider& rt,
			Gdiplus::Color color,
			const OptionData& option,
			bool isSelected,
			CString trackProfileId
		);
		void OnRenderPsrTrack(
			IRadarTargetDataProvider& rt,
			Gdiplus::Color color,
			const OptionData& option
		);
		void OnRenderGroundTrack(
			IRadarTargetDataProvider& rt,
			const CString& callsign,
			Gdiplus::Color color
		);
		void OnRenderFlightPlanTrack(
			IFlightPlanDataProvider& fp,
			Gdiplus::Color color,
			bool isSelected,
			CString trackProfileId
		);

	private:
		std::shared_ptr<ISymbolRenderer> renderer;
		std::shared_ptr<IFlashHelper> flashHelper;
	};
}
