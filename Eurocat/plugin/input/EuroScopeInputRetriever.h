#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin::Input
{
	class EuroScopeInputRetriever
	{
	public:
		virtual ~EuroScopeInputRetriever() = default;
		virtual void OnRetrieveEuroScopeInput(CString str, POINT point, RECT rect) = 0;
	};
}
