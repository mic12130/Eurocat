#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin::Input
{
	class PopupEditDelegate : public std::enable_shared_from_this<PopupEditDelegate>
	{
	public:
		virtual ~PopupEditDelegate() = default;
		virtual void OnSubmit(CString str, POINT point, RECT rect) = 0;
	};
}
