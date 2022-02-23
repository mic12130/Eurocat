#pragma once

namespace Eurocat::Screen
{
	class GraphicsWrapper
	{
	public:
		static GraphicsWrapper CreateDummy()
		{
			HDC dc = HDC();
			Gdiplus::Graphics _graphics(dc);
			return GraphicsWrapper(_graphics);
		}

		GraphicsWrapper(Gdiplus::Graphics& origin);

		void FillRectangle(const Gdiplus::RectF& area, const Gdiplus::Brush& brush) const;
		void FillPolygon(const std::vector<Gdiplus::PointF>& points, const Gdiplus::Brush& brush) const;
		void DrawString(CString text, const Gdiplus::RectF& rect, const Gdiplus::Brush& brush, bool isCenter = false, int fontSize = 9) const;
		void DrawString(CStringW text, const Gdiplus::RectF& rect, const Gdiplus::Brush& brush, bool isCenter = false, int fontSize = 9) const;
		void DrawRectangle(const Gdiplus::RectF& area, const Gdiplus::Pen& pen) const;
		void DrawArc(Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL width, Gdiplus::REAL height, Gdiplus::REAL startAngel, Gdiplus::REAL sweepAngel, const Gdiplus::Pen& pen) const;
		void DrawLine(const Gdiplus::PointF& origin, const Gdiplus::PointF& dest, const Gdiplus::Pen& pen) const;
		void DrawLines(const std::vector<Gdiplus::PointF>& points, const Gdiplus::Pen& pen) const;
		void DrawPolygon(const std::vector<Gdiplus::PointF>& points, const Gdiplus::Pen& pen) const;
		void DrawEllipse(const Gdiplus::PointF& point, Gdiplus::REAL width, Gdiplus::REAL height, const Gdiplus::Pen& pen) const;
		void SetAntialias(bool isEnable) const;
		Gdiplus::SizeF MeasureString(CString text, int fontSize = 9) const;
		Gdiplus::SizeF MeasureString(CStringW text, int fontSize = 9) const;

	private:
		Gdiplus::Graphics& graphics;
		bool isAllowAntialias = false;
	};
}
