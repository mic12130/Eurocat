#pragma once

#include "base/pch.h"

#include "screen/ScreenWrapper.h"
#include "screen/GraphicsWrapper.h"

namespace Eurocat::Hmi::Track
{
	const Gdiplus::REAL kTagLabelContentHeight = 13;

	class ITagLabelContent
	{
	public:
		virtual ~ITagLabelContent() = default;
		virtual void Render(
			Gdiplus::PointF& point,
			Gdiplus::Color color,
			CString trackProfileId,
			Screen::ScreenWrapper& screen,
			Screen::GraphicsWrapper& graphics
		) = 0;
		virtual Gdiplus::SizeF GetSize(Screen::GraphicsWrapper& graphics) = 0;
		virtual bool IsEmpty() = 0;
	};
}
