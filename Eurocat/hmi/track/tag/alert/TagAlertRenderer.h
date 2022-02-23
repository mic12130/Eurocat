#pragma once

#include "screen/ScreenWrapper.h"
#include "screen/GraphicsWrapper.h"
#include "hmi/track/tag/alert/TagAlertData.h"

namespace Eurocat::Hmi::Track
{
	class TagAlertRenderer
	{
	public:
		void RenderAlert(
			TagAlertData& alert,
			Gdiplus::RectF rect,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		);

	private:
		const Gdiplus::Color kRed = Gdiplus::Color(255, 50, 50);
		const Gdiplus::Color kYellow = Gdiplus::Color(255, 255, 0);
		const Gdiplus::Color kBlack = Gdiplus::Color(0, 0, 0);
		const Gdiplus::Color kRedText = Gdiplus::Color(130, 30, 30);
	};
}
