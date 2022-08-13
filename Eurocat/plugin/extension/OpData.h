#pragma once

#include "plugin/extension/OpDataExtraction.h"

namespace Eurocat::Plugin
{
	class OpData
	{
	public:
		// Get OP data text from the ES API.
		// Apart from the scratch pad, the assigned data will be also appended into the result.
		static CString GetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp);

		// Pass OP data input to the ES API.
		// Any assigned data included in the input will be separated and applied individually.
		static void SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, CString content);
	};
}
