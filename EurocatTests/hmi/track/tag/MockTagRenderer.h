#pragma once

#include "pch.h"

#include "hmi/track/tag/ITagRenderer.h"

namespace Eurocat::Hmi::Track
{
	class MockTagRenderer : public ITagRenderer
	{
	public:
		MOCK_METHOD(void, RenderTagLabels, (ITagDataProvider&, Gdiplus::Color, Screen::ScreenWrapper&, Screen::GraphicsWrapper&), (override));
	};
}
