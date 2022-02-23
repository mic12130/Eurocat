#include "base/pch.h"

#include "plugin/extension/FlightPlanAttributeUpdater.h"

#include "common/FlightPlanStateMaker.h"
#include "plugin/Plugin.h"

using namespace Eurocat::Common;

namespace Eurocat::Plugin::Extension
{
	FlightPlanAttributeUpdater::FlightPlanAttributeUpdater(PluginEnvironment& pluginEnv) : pluginEnv(pluginEnv)
	{
	}

	void FlightPlanAttributeUpdater::OnFlightPlanFlightPlanDataUpdate(
		EuroScopePlugIn::CFlightPlan flightPlan)
	{

	}

	void FlightPlanAttributeUpdater::OnFlightPlanControllerAssignedDataUpdate(
		EuroScopePlugIn::CFlightPlan flightPlan, int dataType)
	{
		if (dataType == EuroScopePlugIn::CTR_DATA_TYPE_TEMPORARY_ALTITUDE)
		{
			auto& attribute = pluginEnv.AttributeForFlightPlan(flightPlan);
			attribute.isCflAcknowledged = false;
		}
	}

	void FlightPlanAttributeUpdater::OnTimedEvent(int counter)
	{
		auto& plugin = pluginEnv.GetPlugin();

		for (auto fp = plugin.FlightPlanSelectFirst(); fp.IsValid(); fp = plugin.FlightPlanSelectNext(fp))
		{
			auto state = FlightPlanStateMaker::Make(fp.GetState());
			auto& attribute = pluginEnv.AttributeForFlightPlan(fp);

			if (state != attribute.currentState)
			{
				attribute.lastState = attribute.currentState;
				attribute.currentState = state;
				attribute.lastStateUpdateTime = CTime::GetCurrentTime().GetTime();
			}
		}
	}
}
