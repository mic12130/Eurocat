#include "base/pch.h"

#include "hmi/OptionButton.h"

#include "helper/GraphicsHelper.h"
#include "screen/ScreenObjectType.h"

using namespace Eurocat::Screen;
using namespace Eurocat::Helper;

namespace Eurocat::Hmi
{
	void OptionButton::OnRender(Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		CRect radarArea = screen.GetRadarArea();
		CRect _rect(radarArea.right - 20, radarArea.bottom - 20, radarArea.right, radarArea.bottom);
		Gdiplus::RectF rect = GraphicsHelper::ConvertCRectToRect(_rect);
		Gdiplus::SolidBrush backgroundBrush(Gdiplus::Color(160, 170, 170));
		Gdiplus::SolidBrush textBrush(Gdiplus::Color(96, 0, 0));

		graphics.FillRectangle(rect, backgroundBrush);
		graphics.DrawString("OP", rect, textBrush, true, 9);
		screen.AddScreenObject(ScreenObjectType::kHmiOptionButton, "OPTION_BUTTON", _rect, false, "");
	}

	void OptionButton::OnOverScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args)
	{
	}

	void OptionButton::OnClickScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args)
	{
		if (args.objectType != ScreenObjectType::kHmiOptionButton)
		{
			return;
		}

		if (clickCallback != nullptr)
		{
			clickCallback();
		}
	}

	void OptionButton::OnMoveScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args)
	{
	}

	void OptionButton::SetClickCallback(std::function<void()> callback)
	{
		clickCallback = callback;
	}
}
