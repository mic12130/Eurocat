#pragma once

#include "plugin/PluginEnvironment.h"
#include "plugin/IFlightPlanEventHandler.h"
#include "plugin/ITimedEventHandler.h"

namespace Eurocat::Plugin
{
	class EurocatPlugin;
}

namespace Eurocat::Plugin::Extension
{
	class FlightPlanAttributeUpdater : public IFlightPlanEventHandler, public ITimedEventHandler
	{
	public:
		FlightPlanAttributeUpdater(PluginEnvironment& pluginEnv);
		void OnFlightPlanFlightPlanDataUpdate(EuroScopePlugIn::CFlightPlan flightPlan) override;
		void OnFlightPlanControllerAssignedDataUpdate(EuroScopePlugIn::CFlightPlan flightPlan, int dataType) override;
		void OnTimedEvent(int counter) override;

	private:
		PluginEnvironment& pluginEnv;
	};
}
