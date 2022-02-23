#pragma once

#include "base/pch.h"

#include "screen/GraphicsWrapper.h"
#include "screen/ScreenWrapper.h"
#include "screen/MouseInputArgs.h"

namespace Eurocat::Screen
{
	class IScreenEventHandler
	{
	public:
		virtual ~IScreenEventHandler() = default;
		virtual void OnRender(ScreenWrapper& screen, GraphicsWrapper& graphics) = 0;
		virtual void OnOverScreenObject(ScreenWrapper& screen, MouseInputArgs& args) = 0;
		virtual void OnClickScreenObject(ScreenWrapper& screen, MouseInputArgs& args) = 0;
		virtual void OnMoveScreenObject(ScreenWrapper& screen, MouseInputArgs& args) = 0;
	};
}
