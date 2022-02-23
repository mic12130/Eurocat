#include "base/pch.h"

#include "hmi/track/tag/alert/TagAlertRenderer.h"

using namespace Gdiplus;

namespace Eurocat::Hmi::Track
{
	void TagAlertRenderer::RenderAlert(TagAlertData& alert, Gdiplus::RectF rect, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		auto borderType = alert.GetBorderType();

		if (borderType == BorderType::Yellow)
		{
			graphics.DrawRectangle(rect, Pen(kYellow));
		}
		else if (borderType == BorderType::Red)
		{
			graphics.DrawRectangle(rect, Pen(kRed));
		}
	}
}
