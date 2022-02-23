#pragma once

#include "plugin/input/PopupMenuItem.h"

namespace Eurocat::Plugin::Input
{
	class PopupMenuDelegate : public std::enable_shared_from_this<PopupMenuDelegate>
	{
	public:
		virtual ~PopupMenuDelegate() = default;
		virtual void OnSelectItem(PopupMenuItem item, POINT point, RECT rect) = 0;
	};
}
