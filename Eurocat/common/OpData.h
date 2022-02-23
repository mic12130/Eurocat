#pragma once

#include "base/pch.h"

namespace Eurocat::Common
{
	class OpData
	{
	public:
		static CString GetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp);
		static void SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, CString content);
	};
}
