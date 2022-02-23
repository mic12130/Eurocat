#pragma once

#include "pch.h"

#include "hmi/track/vel/IVelRenderer.h"

namespace Eurocat::Hmi::Track
{
	class MockVelRenderer : public IVelRenderer
	{
	public:
		MOCK_METHOD(void, Render, (IRadarTargetDataProvider&, const TrackProfile&, Gdiplus::Color, int, Screen::ScreenWrapper&, Screen::GraphicsWrapper&), (override));
	};
}
