#include "base/pch.h"

#include "helper/GraphicsHelper.h"

namespace Eurocat::Helper
{
	Gdiplus::RectF GraphicsHelper::ConvertCRectToRect(CRect rect)
	{
		return Gdiplus::RectF(float(rect.left), float(rect.top), float(rect.Width()), float(rect.Height()));
	}

	CRect GraphicsHelper::ConvertRectToCRect(Gdiplus::RectF rect)
	{
		return CRect(int(rect.GetLeft()), int(rect.GetTop()), int(rect.GetRight()), int(rect.GetBottom()));
	}

	Gdiplus::PointF GraphicsHelper::GetPolarPoint(Gdiplus::PointF origin, double heading, double distance)
	{
		double radius = heading / 180 * 3.14;

		return Gdiplus::PointF(
			origin.X + float(lround(distance * sin(radius))),
			origin.Y - float(lround(distance * cos(radius)))
		);
	}
}
