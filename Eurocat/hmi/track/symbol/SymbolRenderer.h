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
		SymbolRenderer(Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics);
		void RenderSsrSymbol(Common::Coordinate coord, Gdiplus::Color color) override;
		void RenderPsrSymbol(Common::Coordinate coord, Gdiplus::Color color) override;
		void RenderGroundTrackSymbol(Common::Coordinate coord, Gdiplus::Color color) override;
		void RenderFlightPlanTrackSymbol(Common::Coordinate coord, Gdiplus::Color color) override;
		void RenderSelectedSymbol(Common::Coordinate coord, Gdiplus::Color color) override;
		void AddScreenObject(Common::Coordinate coord, CString objectId, CString message) override;

	private:
		Screen::ScreenWrapper& screen;
		Screen::GraphicsWrapper& graphics;
		Gdiplus::PointF GetPx(Common::Coordinate coord, Screen::ScreenWrapper& screen);
	};
}
