#pragma once

#include "base/pch.h"

#include "screen/MouseButton.h"

namespace Eurocat::Screen
{
	class MouseInputArgs
	{
	public:
		int objectType;
		CString objectId;
		POINT point;
		RECT rect;
		MouseButton mouseButton;
		bool isReleased;

		MouseInputArgs(
			int objectType, CString objectId, POINT point, RECT rect,
			MouseButton mouseButton, bool isReleased = true)
			: objectType(objectType), objectId(objectId), point(point), rect(rect),
			mouseButton(mouseButton), isReleased(isReleased)
		{
		}
	};
}
