#include "base/pch.h"

#include "hmi/track/symbol/SymbolRenderer.h"

#include "helper/CoordinateHelper.h"
#include "screen/ScreenObjectType.h"

using namespace Gdiplus;
using namespace Eurocat::Helper;
using namespace Eurocat::Screen;

namespace Eurocat::Hmi::Track
{
	SymbolRenderer::SymbolRenderer(Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
		: screen(screen), graphics(graphics)
	{
	}

	void SymbolRenderer::RenderSsrSymbol(Common::Coordinate coord, Gdiplus::Color color)
	{
		PointF px = GetPx(coord, screen);
		Pen pen(color, REAL(2));

		graphics.SetAntialias(true);
		graphics.DrawArc(px.X - 6, px.Y - 6, 12, 12, REAL(0), REAL(360), pen);
		graphics.SetAntialias(false);
	}

	void SymbolRenderer::RenderPsrSymbol(Common::Coordinate coord, Gdiplus::Color color)
	{
		PointF px = GetPx(coord, screen);
		Pen pen(color, REAL(1));

		graphics.SetAntialias(true);
		graphics.DrawLine(PointF(px.X - 4, px.Y), PointF(px.X + 4, px.Y), pen);
		graphics.DrawLine(PointF(px.X, px.Y - 4), PointF(px.X, px.Y + 4), pen);
		graphics.SetAntialias(false);
	}

	void SymbolRenderer::RenderGroundTrackSymbol(Common::Coordinate coord, Gdiplus::Color color)
	{
		PointF px = GetPx(coord, screen);
		Pen pen(color, REAL(2));

		graphics.SetAntialias(true);
		graphics.DrawArc(px.X - 3, px.Y - 3, 5, 5, REAL(0), REAL(360), pen);
		graphics.SetAntialias(false);
	}

	void SymbolRenderer::RenderFlightPlanTrackSymbol(Common::Coordinate coord, Gdiplus::Color color)
	{
		PointF px = GetPx(coord, screen);
		Pen pen(color, REAL(2));
		std::vector<PointF> points{
			PointF(px.X + 6, px.Y + 6),
			PointF(px.X + 6, px.Y - 6),
			PointF(px.X - 6, px.Y - 6),
			PointF(px.X - 6, px.Y + 6),
			PointF(px.X + 6, px.Y + 6)
		};

		graphics.SetAntialias(true);
		graphics.DrawLines(points, pen);
		graphics.SetAntialias(false);
	}

	void SymbolRenderer::RenderSelectedSymbol(Common::Coordinate coord, Gdiplus::Color color)
	{
		PointF px = GetPx(coord, screen);
		Pen pen(color, REAL(2));
		std::vector<PointF> points{
			PointF(px.X + 5, px.Y + 10),
			PointF(px.X + 10, px.Y + 5),
			PointF(px.X + 10, px.Y - 5),
			PointF(px.X + 5, px.Y - 10),
			PointF(px.X - 5, px.Y - 10),
			PointF(px.X - 10, px.Y - 5),
			PointF(px.X - 10, px.Y + 5),
			PointF(px.X - 5, px.Y + 10),
			PointF(px.X + 5, px.Y + 10)
		};

		graphics.SetAntialias(true);
		graphics.DrawLines(points, pen);
		graphics.SetAntialias(false);
	}

	void SymbolRenderer::AddScreenObject(Common::Coordinate coord, const SymbolObjectInfo& info)
	{
		PointF px = GetPx(coord, screen);
		CRect area(int(px.X) - 6, int(px.Y) - 6, int(px.X) + 6, int(px.Y) + 6);
		screen.AddScreenObject(ScreenObjectType::kTrack, info.objectId, area, false, info.message);
	}

	Gdiplus::PointF SymbolRenderer::GetPx(Common::Coordinate coord, Screen::ScreenWrapper& screen)
	{
		auto _coord = CoordinateHelper::ConvertToCPosition(coord);
		auto _px = screen.ConvertCoordFromPositionToPixel(_coord);

		return PointF(float(_px.x), float(_px.y));
	}
}
