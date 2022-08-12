#pragma once

#include "hmi/FlightPlanDisplayState.h"
#include "plugin/extension/FlightPlanAttribute.h"

namespace Eurocat::Hmi
{
	class FlightPlanDisplayStateGenerator
	{
	public:
		static auto Generate(EuroScopePlugIn::CFlightPlan& fp) -> FlightPlanDisplayState;
		static bool IsAcceptedReminding(EuroScopePlugIn::CFlightPlan& fp);
	};
}
