#pragma once

#include "plugin/IFlightPlanEventHandler.h"
#include "plugin/ITimedEventHandler.h"
#include "plugin/Plugin.h"

namespace Eurocat::Plugin::Extension
{
	// Updates flight plans to make them meet the requirements of Eurocat plugin.
	// To avoid possible conflict, changes will be only applied on controlled flight plans.
	// Current processing items:
	// - Passes assigned data to label data
	class FlightPlanProcessor : public ITimedEventHandler
	{
	public:
		FlightPlanProcessor(EurocatPlugin& plugin);
		void OnTimedEvent(int counter) override;

	private:
		EurocatPlugin& plugin;

		void PassAssignedDataToLabelDataIfNeeded(EuroScopePlugIn::CFlightPlan& fp);
	};
}
