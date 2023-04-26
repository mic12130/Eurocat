#include "base/pch.h"

#include "plugin/extension/FlightPlanAttributeUpdater.h"

#include "common/FlightPlanStateMaker.h"
#include "plugin/PluginAccess.h"

using namespace Eurocat::Common;

namespace Eurocat::Plugin
{
	FlightPlanAttributeUpdater::FlightPlanAttributeUpdater(EuroScopePlugIn::CPlugIn& plugin)
		: plugin(plugin)
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
			auto& attribute = PluginAccess::Shared().FlightPlanAttribute (flightPlan);
			attribute.isCflAcknowledged = false;
		}
	}

	void FlightPlanAttributeUpdater::OnTimedEvent(int counter)
	{
		for (auto fp = plugin.FlightPlanSelectFirst(); fp.IsValid(); fp = plugin.FlightPlanSelectNext(fp))
		{
			auto state = FlightPlanStateMaker::Make(fp.GetState());
			auto& attribute = PluginAccess::Shared().FlightPlanAttribute(fp);

			if (state != attribute.currentState)
			{
				attribute.lastState = attribute.currentState;
				attribute.currentState = state;
				attribute.lastStateUpdateTime = CTime::GetCurrentTime().GetTime();
			}
		}
	}
}
