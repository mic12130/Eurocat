#pragma once

#include "hmi/cursor/CursorType.h"

namespace Eurocat::Hmi::Cursor
{
	class ICursorManager
	{
	public:
		virtual ~ICursorManager() = default;
		virtual void OnRender() = 0;
		virtual void OnScreenToBeClosed() = 0;
		virtual void SetCursorType(CursorType type) = 0;
	};
}
