#pragma once

#include "base/pch.h"

namespace Eurocat::Helper
{
	class GraphicsHelper
	{
	public:
		static Gdiplus::RectF ConvertCRectToRect(CRect rect);
		static CRect ConvertRectToCRect(Gdiplus::RectF rect);
		static Gdiplus::PointF GetPolarPoint(Gdiplus::PointF origin, double heading, double distance);
	};
}
