#include "base/pch.h"

#include "plugin/PluginEnvironment.h"

#include "common/FlightPlanStateMaker.h"

using namespace Eurocat::Plugin::Extension;
using namespace Eurocat::Common;

namespace Eurocat::Plugin
{
	PluginEnvironment& PluginEnvironment::Shared()
	{
		return *shared;
	}

	void PluginEnvironment::SetShared(std::shared_ptr<PluginEnvironment> ptr)
	{
		shared = std::move(ptr);
	}

	PluginEnvironment::PluginEnvironment(EuroScopePlugIn::CPlugIn& plugin) : plugin(plugin)
	{
	}

	Extension::FlightPlanAttribute& PluginEnvironment::AttributeForFlightPlan(EuroScopePlugIn::CFlightPlan flightPlan)
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

	EuroScopePlugIn::CPlugIn& PluginEnvironment::GetPlugin()
	{
		return plugin;
	}

	PluginEnvironment PluginEnvironment::CreateDummy()
	{
		EuroScopePlugIn::CPlugIn plugin(0, "", "", "", "");
		return PluginEnvironment(plugin);
	}
}
