#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin
{
	class IFlightPlanEventHandler
	{
	public:
		virtual ~IFlightPlanEventHandler() = default;
		virtual void OnFlightPlanFlightPlanDataUpdate(EuroScopePlugIn::CFlightPlan flightPlan) = 0;
		virtual void OnFlightPlanControllerAssignedDataUpdate(EuroScopePlugIn::CFlightPlan flightPlan, int dataType) = 0;
	};
}
