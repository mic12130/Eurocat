#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin
{
	class FlightPlanHelper
	{
	public:
		static bool IsWritable(const EuroScopePlugIn::CFlightPlan& fp)
		{
			if (fp.GetTrackingControllerIsMe() || CString(fp.GetTrackingControllerCallsign()).IsEmpty())
			{
				return true;
			}

			return false;
		}
	};
}
