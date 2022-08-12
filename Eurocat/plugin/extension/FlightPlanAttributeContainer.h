#pragma once

#include "plugin/extension/FlightPlanAttribute.h"

namespace Eurocat::Plugin
{
	class FlightPlanAttributeContainer
	{
	public:
		static FlightPlanAttributeContainer& Shared();

		FlightPlanAttribute& AttributeForFlightPlan(EuroScopePlugIn::CFlightPlan flightPlan);
	private:
		static std::shared_ptr<FlightPlanAttributeContainer> shared;

		FlightPlanAttributeContainer() = default;

		std::map<CString, FlightPlanAttribute> flightPlanAttributeMap;
	};
}
