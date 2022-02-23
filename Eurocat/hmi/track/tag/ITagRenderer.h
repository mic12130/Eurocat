#pragma once

#include "base/pch.h"

#include "screen/ScreenWrapper.h"
#include "screen/GraphicsWrapper.h"
#include "hmi/track/tag/render_data/ITagDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class ITagRenderer
	{
	public:
		virtual ~ITagRenderer() = default;
		virtual void RenderTagLabels(
			ITagDataProvider& tagData,
			Gdiplus::Color color,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		) = 0;
	};
}
