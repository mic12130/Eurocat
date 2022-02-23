#pragma once

#include "pch.h"

#include "hmi/track/hist/IHistRenderer.h"

namespace Eurocat::Hmi::Track
{
	class MockHistRenderer : public IHistRenderer
	{
	public:
		MOCK_METHOD(void, Render, (std::vector<Common::Coordinate>, Gdiplus::Color, Screen::ScreenWrapper&, Screen::GraphicsWrapper&), (override));
	};
}
