#pragma once

#include "plugin/IFlightPlanEventHandler.h"
#include "plugin/ITimedEventHandler.h"

namespace Eurocat::Plugin
{
	class EurocatPlugin;
}

namespace Eurocat::Plugin
{
	class FlightPlanAttributeUpdater : public IFlightPlanEventHandler, public ITimedEventHandler
	{
	public:
		FlightPlanAttributeUpdater(EuroScopePlugIn::CPlugIn& plugin);
		void OnFlightPlanFlightPlanDataUpdate(EuroScopePlugIn::CFlightPlan flightPlan) override;
		void OnFlightPlanControllerAssignedDataUpdate(EuroScopePlugIn::CFlightPlan flightPlan, int dataType) override;
		void OnTimedEvent(int counter) override;

	private:
		EuroScopePlugIn::CPlugIn& plugin;
	};
}
