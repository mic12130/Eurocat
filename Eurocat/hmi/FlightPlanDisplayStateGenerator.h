#pragma once

#include "hmi/FlightPlanDisplayState.h"
#include "plugin/extension/FlightPlanAttribute.h"

namespace Eurocat::Hmi
{
	class FlightPlanDisplayStateGenerator
	{
	public:
		static auto Generate(
			const EuroScopePlugIn::CFlightPlan& fp, 
			const Plugin::Extension::FlightPlanAttribute& fpAttribute
		) -> FlightPlanDisplayState;
	};
}
