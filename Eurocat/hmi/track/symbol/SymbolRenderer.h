#pragma once

#include "hmi/track/symbol/ISymbolRenderer.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "screen/GraphicsWrapper.h"

namespace Eurocat::Hmi::Track
{
	class SymbolRenderer : public ISymbolRenderer
	{
	public:
		void RenderSsrSymbol(Common::Coordinate coord, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics) override;
		void RenderPsrSymbol(Common::Coordinate coord, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics) override;
		void RenderGroundTrackSymbol(Common::Coordinate coord, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics) override;
		void RenderFlightPlanTrackSymbol(Common::Coordinate coord, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics) override;
		void RenderSelectedSymbol(Common::Coordinate coord, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics) override;
		void AddScreenObject(Common::Coordinate coord, CString objectId, CString message, Screen::ScreenWrapper& screen) override;

	private:
		Gdiplus::PointF GetPx(Common::Coordinate coord, Screen::ScreenWrapper& screen);
	};
}
