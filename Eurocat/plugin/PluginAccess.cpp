#include "base/pch.h"

#include "plugin/PluginAccess.h"

namespace Eurocat::Plugin
{
	std::shared_ptr<PluginAccess> PluginAccess::shared = nullptr;

	PluginAccess& PluginAccess::Shared()
	{
		return *shared;
	}

	void PluginAccess::SetupShared(std::shared_ptr<Plugin::EurocatPlugin> plugin)
	{
		shared = std::make_shared<PluginAccess>(plugin);
	}

	EurocatPlugin& PluginAccess::GetPlugin()
	{
		return *plugin;
	}

	FlightPlanAttribute& PluginAccess::FlightPlanAttribute(EuroScopePlugIn::CFlightPlan flightPlan)
	{
		return flightPlanAttributeContainer->AttributeForFlightPlan(flightPlan);
	}

	PluginAccess::PluginAccess(std::shared_ptr<Plugin::EurocatPlugin> plugin)
		: plugin(std::move(plugin)),
		flightPlanAttributeContainer(std::make_unique<FlightPlanAttributeContainer>())
	{
	}
}