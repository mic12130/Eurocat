#include "base/pch.h"

#include "plugin/extension/FlightPlanAttributeContainer.h"

#include "common/FlightPlanStateMaker.h"

using namespace Eurocat::Common;

namespace Eurocat::Plugin
{
	FlightPlanAttribute& FlightPlanAttributeContainer::AttributeForFlightPlan(EuroScopePlugIn::CFlightPlan flightPlan)
	{
		CString callsign = flightPlan.GetCallsign();

		if (flightPlanAttributeMap.find(callsign) == flightPlanAttributeMap.end())
		{
			FlightPlanAttribute newAttribute;
			newAttribute.isCflAcknowledged = false;
			newAttribute.currentState = FlightPlanStateMaker::Make(flightPlan.GetState());
			newAttribute.lastState = FlightPlanStateMaker::Make(flightPlan.GetState());
			newAttribute.lastStateUpdateTime = CTime::GetCurrentTime().GetTime();

			flightPlanAttributeMap[callsign] = newAttribute;
		}

		return flightPlanAttributeMap[callsign];
	}
}
