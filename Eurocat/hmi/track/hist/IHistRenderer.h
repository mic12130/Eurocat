#pragma once

#include "base/pch.h"

#include "common/Coordinate.h"
#include "screen/ScreenWrapper.h"
#include "screen/GraphicsWrapper.h"

namespace Eurocat::Hmi::Track
{
	class IHistRenderer
	{
	public:
		virtual ~IHistRenderer() = default;
		virtual void Render(
			std::vector<Common::Coordinate> positions,
			Gdiplus::Color color,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		) = 0;
	};
}
