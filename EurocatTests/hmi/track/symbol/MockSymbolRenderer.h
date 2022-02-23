#pragma once

#include "pch.h"

#include "hmi/track/symbol/ISymbolRenderer.h"

namespace Eurocat::Hmi::Track
{
	class MockSymbolRenderer : public ISymbolRenderer
	{
	public:
		MOCK_METHOD(void, RenderSsrSymbol, (Common::Coordinate, Gdiplus::Color, Screen::ScreenWrapper&, Screen::GraphicsWrapper&), (override));
		MOCK_METHOD(void, RenderPsrSymbol, (Common::Coordinate, Gdiplus::Color, Screen::ScreenWrapper&, Screen::GraphicsWrapper&), (override));
		MOCK_METHOD(void, RenderGroundTrackSymbol, (Common::Coordinate, Gdiplus::Color, Screen::ScreenWrapper&, Screen::GraphicsWrapper&), (override));
		MOCK_METHOD(void, RenderFlightPlanTrackSymbol, (Common::Coordinate, Gdiplus::Color, Screen::ScreenWrapper&,Screen::GraphicsWrapper&), (override));
		MOCK_METHOD(void, RenderSelectedSymbol, (Common::Coordinate, Gdiplus::Color, Screen::ScreenWrapper&, Screen::GraphicsWrapper&), (override));
		MOCK_METHOD(void, AddScreenObject, (Common::Coordinate, CString, CString, Screen::ScreenWrapper&), (override))
		;
	};
}
