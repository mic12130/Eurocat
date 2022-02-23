#pragma once

#include "plugin/input/PopupMenuItem.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Window
{
	class LevelPopupMenuDelegate : public std::enable_shared_from_this<LevelPopupMenuDelegate>
	{
	public:
		virtual ~LevelPopupMenuDelegate() = default;
		virtual void OnSelectLevel(int level, Hmi::Unit::UnitDisplayMode unit) = 0;
	};
}
