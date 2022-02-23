#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin
{
	class IFunctionHandler
	{
	public:
		virtual ~IFunctionHandler() = default;
		virtual void OnFunctionCall(int functionId, CString itemString, POINT point, RECT area) = 0;
	};
}
