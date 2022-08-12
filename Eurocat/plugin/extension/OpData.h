#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin
{
	class OpData
	{
	public:
		static CString GetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp);
		static void SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, CString content);
	};
}
