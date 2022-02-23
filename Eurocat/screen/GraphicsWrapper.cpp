#include "base/pch.h"

#include "screen/GraphicsWrapper.h"

#include "screen/WindowScalingInfo.h"

using namespace Gdiplus;

namespace Eurocat::Screen
{
	GraphicsWrapper::GraphicsWrapper(Gdiplus::Graphics& origin) : graphics(origin)
	{
		origin.SetPageUnit(Gdiplus::UnitPixel);
		origin.SetSmoothingMode(SmoothingModeHighSpeed);
		origin.SetTextRenderingHint(TextRenderingHintAntiAlias);

		isAllowAntialias = WindowScalingInfo::GetScaleFactor() <= 1.25;
	}

	void GraphicsWrapper::FillRectangle(const RectF& area, const Brush& brush) const
	{
		graphics.FillRectangle(&brush, area);
	}

	void GraphicsWrapper::FillPolygon(const std::vector<Gdiplus::PointF>& points, const Brush& brush) const
	{
		graphics.FillPolygon(&brush, &points[0], points.size());
	}

	void GraphicsWrapper::DrawString(CString text, const RectF& rect, const Brush& brush, bool isCenter, int fontSize) const
	{
		CStringW wstr(text);
		DrawString(wstr, rect, brush, isCenter, fontSize);
	}

	void GraphicsWrapper::DrawString(CStringW text, const Gdiplus::RectF& rect, const Gdiplus::Brush& brush, bool isCenter, int fontSize) const
	{
		FontFamily fontFamily(L"DejaVu Sans Mono");
		Font font(&fontFamily, REAL(fontSize), FontStyleRegular);
		StringFormat format = StringFormat::GenericTypographic();

		format.SetLineAlignment(isCenter ? StringAlignmentCenter : StringAlignmentNear);
		format.SetAlignment(isCenter ? StringAlignmentCenter : StringAlignmentNear);
		format.SetFormatFlags(StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces);

		graphics.DrawString(text, text.GetLength(), &font, rect, &format, &brush);
	}

	void GraphicsWrapper::DrawRectangle(const RectF& area, const Pen& pen) const
	{
		graphics.DrawRectangle(&pen, area);
	}

	void GraphicsWrapper::DrawArc(REAL x, REAL y, REAL width, REAL height, REAL startAngel, REAL sweepAngel, const Gdiplus::Pen& pen) const
	{
		graphics.DrawArc(&pen, x, y, width, height, startAngel, sweepAngel);
	}

	void GraphicsWrapper::DrawLine(const PointF& origin, const PointF& dest, const Pen& pen) const
	{
		graphics.DrawLine(&pen, origin, dest);
	}

	void GraphicsWrapper::DrawLines(const std::vector<Gdiplus::PointF>& points, const Gdiplus::Pen& pen) const
	{
		graphics.DrawLines(&pen, &points[0], points.size());
	}

	void GraphicsWrapper::DrawPolygon(const std::vector<Gdiplus::PointF>& points, const Pen& pen) const
	{
		graphics.DrawPolygon(&pen, &points[0], points.size());
	}

	void GraphicsWrapper::DrawEllipse(const PointF& point, REAL width, REAL height, const Pen& pen) const
	{
		graphics.DrawEllipse(&pen, point.X, point.Y, width, height);
	}

	void GraphicsWrapper::SetAntialias(bool isEnable) const
	{
		if (!isAllowAntialias)
		{
			return;
		}

		graphics.SetSmoothingMode(isEnable ? SmoothingModeHighQuality : SmoothingModeHighSpeed);
	}

	SizeF GraphicsWrapper::MeasureString(CString text, int fontSize) const
	{
		CStringW wstr(text);
		return MeasureString(wstr, fontSize);
	}

	Gdiplus::SizeF GraphicsWrapper::MeasureString(CStringW text, int fontSize) const
	{
		RectF stringRect;
		RectF layoutRect(0, 0, 600, 100);
		FontFamily fontFamily(L"DejaVu Sans Mono");
		Font font(&fontFamily, REAL(fontSize), FontStyleRegular);
		StringFormat format = StringFormat::GenericTypographic();

		format.SetLineAlignment(StringAlignmentNear);
		format.SetAlignment(StringAlignmentNear);
		format.SetFormatFlags(StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces);

		graphics.MeasureString(text, text.GetLength(), &font, layoutRect, &format, &stringRect);

		return SizeF(stringRect.Width, stringRect.Height);
	}
}
