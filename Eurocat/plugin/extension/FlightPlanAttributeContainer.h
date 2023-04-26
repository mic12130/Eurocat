#pragma once

#include "plugin/extension/FlightPlanAttribute.h"

namespace Eurocat::Plugin
{
	class FlightPlanAttributeContainer
	{
	public:
		FlightPlanAttributeContainer() = default;
		FlightPlanAttribute& AttributeForFlightPlan(EuroScopePlugIn::CFlightPlan flightPlan);
	private:
		std::map<CString, FlightPlanAttribute> flightPlanAttributeMap;
	};
}
