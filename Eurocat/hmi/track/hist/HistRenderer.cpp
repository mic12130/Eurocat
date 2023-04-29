#include "base/pch.h"

#include "hmi/track/hist/HistRenderer.h"
#include "helper/CoordinateHelper.h"
#include "helper/GraphicsHelper.h"

using namespace Gdiplus;
using namespace Eurocat::Helper;

namespace Eurocat::Hmi::Track
{
	void HistRenderer::Render(std::vector<Common::Coordinate> positions, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		for (auto& position : positions)
		{
			SolidBrush brush(color);
			POINT _px = screen.ConvertCoordFromPositionToPixel(CoordinateHelper::ConvertToCPosition(position));
			PointF px(float(_px.x), float(_px.y));

			std::vector points = {
				PointF(px.X - 2, px.Y),
				PointF(px.X, px.Y - 2),
				PointF(px.X + 2, px.Y),
				PointF(px.X, px.Y + 2)
			};

			graphics.FillPolygon(points, brush);
		}
	}
}
