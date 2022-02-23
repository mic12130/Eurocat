#pragma once

#include "plugin/PluginEnvironment.h"
#include "plugin/IFlightPlanEventHandler.h"
#include "plugin/ITimedEventHandler.h"

namespace Eurocat::Plugin::Extension
{
	// Updates flight plans to make them meet the requirements of Eurocat plugin.
	// To avoid possible conflict, changes will be only applied on controlled flight plans.
	// Current processing items:
	// - Passes assigned data to label data
	class FlightPlanProcessor : public ITimedEventHandler
	{
	public:
		FlightPlanProcessor(PluginEnvironment& pluginEnv);
		void OnTimedEvent(int counter) override;

	private:
		void PassAssignedDataToLabelDataIfNeeded(EuroScopePlugIn::CFlightPlan& fp);

		PluginEnvironment& pluginEnv;
	};
}
