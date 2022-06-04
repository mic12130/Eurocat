#include "base/pch.h"

#include "hmi/track/tag/TagRenderer.h"

#include "hmi/track/tag/alert/TagAlertRenderer.h"
#include "hmi/track/tag/RepositionHelper.h"
#include "hmi/track/TrackObjectId.h"
#include "hmi/track/FlashHelper.h"
#include "helper/CoordinateHelper.h"
#include "screen/ScreenObjectType.h"

using namespace Gdiplus;
using namespace Eurocat::Helper;
using namespace Eurocat::Screen;

namespace Eurocat::Hmi::Track
{
	void TagRenderer::RenderTagLabels(ITagDataProvider& tagData, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		if (tagData.GetIsRepositioning())
		{
			RenderRepositioning(tagData.GetPosition(), tagData, screen, graphics);
			return;
		}

		// When flashing off, labels are invisible but screen objects will be added still
		bool isLabelHidden = tagData.GetIsFlashing() && FlashHelper::Regular()->ShouldRender() == false;

		TagLabelCollection labelCollection = tagData.GetLabels();
		auto tagOffset = tagData.GetOffset();
		auto _coord = Helper::CoordinateHelper::ConvertToCPosition(tagData.GetPosition());
		POINT _positionPx = screen.ConvertCoordFromPositionToPixel(_coord);
		PointF positionPx(float(_positionPx.x), float(_positionPx.y));
		PointF anchor(positionPx.X + float(std::get<0>(tagOffset)), positionPx.Y + float(std::get<1>(tagOffset)));
		auto labelContents = GetLabelContents(tagData.GetLabels());
		Gdiplus::REAL labelWidth = GetLabelWidth(labelContents, graphics);
		Gdiplus::REAL labelHeight = GetLabelHeight(labelContents, graphics);

		// The position where we start the label rendering
		// We align the right side of the label to the anchor if we have minus tagOffsetX
		PointF labelOrigin(
			std::get<0>(tagOffset) < 0 ? (anchor.X - labelWidth) : anchor.X,
			anchor.Y - 2 * kLineSeparation
		);

		PointF tempPoint(labelOrigin); // A temporary point used by tag label rendering

		for (auto& labelLine : labelContents)
		{
			for each (auto label in labelLine)
			{
				if (!isLabelHidden)
				{
					label->Render(tempPoint, color, graphics);
				}

				label->AddScreenObject(tempPoint, tagData.GetProfileId(), screen, graphics);
				label->MovePoint(tempPoint, graphics);
			}

			// Set px to the beginning of the next line
			tempPoint.X = labelOrigin.X;
			tempPoint.Y += kLineSeparation;
		}

		if (!isLabelHidden)
		{
			// Leader line between target point and tag anchor
			Pen pen(color);
			graphics.DrawLine(positionPx, anchor, pen);

			// Alert
			RectF alertRect(labelOrigin.X, labelOrigin.Y, labelWidth, labelHeight);
			TagAlertData alertData = tagData.GetAlertData();
			TagAlertRenderer().RenderAlert(alertData, alertRect, screen, graphics);
		}
	}

	auto TagRenderer::GetLabelContents(TagLabelCollection labelCollection) -> std::vector<std::vector<std::shared_ptr<ITagLabelContent>>>
	{
		std::vector<std::vector<std::shared_ptr<ITagLabelContent>>> result;

		for (auto& labelLine : labelCollection)
		{
			result.emplace_back();

			for (auto& label : labelLine)
			{
				result.back().push_back(label->GetTagLabelContent());
			}
		}

		return result;
	}

	Gdiplus::REAL TagRenderer::GetLabelWidth(
		const std::vector<std::vector<std::shared_ptr<ITagLabelContent>>>& labelContents,
		Screen::GraphicsWrapper& graphics)
	{
		REAL labelWidth = 0;

		// Loop through label lines and find the line that has the greatest width
		for each (auto labelLine in labelContents)
		{
			REAL lineWidth = 0;
			for each (auto label in labelLine)
			{
				lineWidth += label->GetSize(graphics).Width;
			}

			if (lineWidth > labelWidth)
			{
				labelWidth = lineWidth;
			}
		}

		return labelWidth;
	}

	Gdiplus::REAL TagRenderer::GetLabelHeight(
		const std::vector<std::vector<std::shared_ptr<ITagLabelContent>>>& labelContents,
		Screen::GraphicsWrapper& graphics)
	{
		REAL result = float(labelContents.size()) * kLineSeparation;

		for (auto& labelLine : labelContents)
		{
			bool isEmptyLine = true;

			for each (auto label in labelLine)
			{
				if (!label->IsEmpty())
				{
					isEmptyLine = false;
					break;
				}
			}

			// Only last line's empty could affect the label height
			if (isEmptyLine && labelLine == labelContents.back())
			{
				result = result - kLineSeparation;
			}
		}

		return result;
	}

	void TagRenderer::RenderRepositioning(Common::Coordinate coord, ITagDataProvider& tagData,
		Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		// Available Degrees: 0, 22.5, 45, 67.5...157.5, 180
		// Available Length: 30, 60, 100 (in px)
		Pen pen(Color::White);
		CPoint targetPx = screen.ConvertCoordFromPositionToPixel(CoordinateHelper::ConvertToCPosition(coord));
		CPoint cursorPx;
		CPoint closestPolarPx;
		RectF rect;

		GetCursorPos(&cursorPx);
		closestPolarPx = RepositionHelper::GetClosestPolarPx(targetPx, cursorPx);

		if (closestPolarPx.x < targetPx.x)
		{
			rect = RectF(
				float(closestPolarPx.x) - 96,
				float(closestPolarPx.y) - 2 * kLineSeparation,
				96, kLineSeparation * 4
			);
		}
		else
		{
			rect = RectF(
				float(closestPolarPx.x),
				float(closestPolarPx.y) - 2 * kLineSeparation,
				96, kLineSeparation * 4
			);
		}

		graphics.SetAntialias(true);
		graphics.DrawLine(
			PointF(float(targetPx.x), float(targetPx.y)),
			PointF(float(closestPolarPx.x), float(closestPolarPx.y)),
			pen
		);
		graphics.SetAntialias(false);
		graphics.DrawRectangle(rect, pen);

		screen.AddScreenObject(
			ScreenObjectType::kTrack, TrackObjectId::kRepositioningBackgroundObjectId,
			screen.GetRadarArea(),
			false, ""
		);
		screen.RequestRefresh();
	}
}
