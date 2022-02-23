#pragma once

#include "screen/IScreenEventHandler.h"

namespace Eurocat::Hmi
{
	class OptionButton : public Screen::IScreenEventHandler
	{
	public:
		void OnRender(Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics) override;
		void OnOverScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args) override;
		void OnClickScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args) override;
		void OnMoveScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args) override;
		void SetClickCallback(std::function<void()> callback);

	private:
		std::function<void()> clickCallback;
	};
}
