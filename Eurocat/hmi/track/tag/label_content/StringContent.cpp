#include "base/pch.h"

#include "hmi/track/tag/label_content/StringContent.h"

#include "helper/GraphicsHelper.h"
#include "screen/ScreenObjectType.h"
#include "hmi/track/TrackObjectId.h"

using namespace Gdiplus;
using namespace Eurocat::Helper;
using namespace Eurocat::Screen;

namespace Eurocat::Hmi::Track
{
	StringContent::StringContent(CString str, CString objectIdSuffix) : StringContent(CStringW(str), objectIdSuffix)
	{
	}

	StringContent::StringContent(CStringW str, CString objectIdSuffix, bool hasUnderline, std::optional<Gdiplus::Color> overridenColor, std::optional<Gdiplus::Color> backgroundColor)
		: string(str),
		objectIdSuffix(objectIdSuffix),
		hasUnderline(hasUnderline),
		overridenColor(overridenColor),
		backgroundColor(backgroundColor)
	{
	}

	void StringContent::Render(const Gdiplus::PointF& point, Gdiplus::Color color, Screen::GraphicsWrapper& graphics)
	{
		if (string == "")
		{
			return;
		}

		SizeF size = GetSize(graphics);
		RectF rect(point.X, point.Y, size.Width, size.Height);
		Color actualColor = overridenColor.has_value() ? overridenColor.value() : color;
		SolidBrush brush(actualColor);

		// The background rect has to be rendered before the text
		if (backgroundColor.has_value())
		{
			SolidBrush backgroundBrush(backgroundColor.value());
			graphics.FillRectangle(rect, backgroundBrush);
		}

		graphics.DrawString(string, rect, brush);

		if (hasUnderline)
		{
			Pen pen = Pen(actualColor);
			PointF origin = PointF(rect.GetLeft(), rect.GetBottom() + 1);
			PointF dest = PointF(rect.GetRight(), rect.GetBottom() + 1);
			graphics.DrawLine(origin, dest, pen);
		}
	}

	void StringContent::AddScreenObject(const Gdiplus::PointF& point, CString trackProfileId, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		SizeF size = GetSize(graphics);
		RectF rect(point.X, point.Y, size.Width, size.Height);

		if (objectIdSuffix != "")
		{
			CString objectId = TrackObjectId::Generate(trackProfileId, objectIdSuffix);
			screen.AddScreenObject(ScreenObjectType::kTrack, objectId, GraphicsHelper::ConvertRectToCRect(rect), false, "");
		}
	}

	void StringContent::MovePoint(Gdiplus::PointF& point, Screen::GraphicsWrapper& graphics)
	{
		SizeF size = GetSize(graphics);
		RectF rect(point.X, point.Y, size.Width, size.Height);
		point.X += rect.Width;
	}

	Gdiplus::SizeF StringContent::GetSize(Screen::GraphicsWrapper& graphics)
	{
		return { kCharWidth * string.GetLength(), kTagLabelContentHeight };
	}

	bool StringContent::IsEmpty()
	{
		// In some cases we would fill the label with some spaces when it was empty, to
		// create a clickable area (label data), so an additional trim is necessary here
		CString str(string);
		return str.Trim().IsEmpty();
	}
}
