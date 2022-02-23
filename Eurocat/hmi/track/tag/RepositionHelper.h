#pragma once

#include "base/pch.h"

#include "helper/GraphicsHelper.h"

namespace Eurocat::Hmi::Track
{
	class RepositionHelper
	{
	public:
		static CPoint GetClosestPolarPx(CPoint targetPx, CPoint cursorPx)
		{
			// Calculate px data
			int closestDegrees, closestLength;
			int length = (int)sqrt(pow(targetPx.x - cursorPx.x, 2) + pow(targetPx.y - cursorPx.y, 2));
			double scale = (targetPx.y - cursorPx.y) / (double)length;
			int degrees = (int)(acos(scale) / 3.14 * 180);

			if (cursorPx.x < targetPx.x)
			{
				degrees = -degrees;
			}

			// Find the closest degrees
			if (degrees > 0)
			{
				closestDegrees = int(int((degrees + 11) / 22.5) * 22.5);
			}
			else
			{
				closestDegrees = int(int((degrees - 11) / 22.5) * 22.5);
			}

			// Find the closest length
			if (length > 120)
			{
				closestLength = 120;
			}
			else if (length > 80)
			{
				closestLength = 80;
			}
			else
			{
				closestLength = 40;
			}

			auto _result = Helper::GraphicsHelper::GetPolarPoint(
				Gdiplus::PointF(float(targetPx.x), float(targetPx.y)),
				closestDegrees, closestLength
			);

			return {int(_result.X), int(_result.Y)};
		}
	};
}