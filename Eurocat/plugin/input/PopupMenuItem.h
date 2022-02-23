#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin::Input
{
	struct PopupMenuItem
	{
		CString text;
		bool selected = false;

		PopupMenuItem(CString text) : text(text)
		{
		}

		PopupMenuItem(CString text, bool selected)
			: text(text), selected(selected)
		{

		}
	};
}
