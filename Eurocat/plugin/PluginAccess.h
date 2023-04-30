#pragma once

#include "plugin/Plugin.h"
#include "plugin/extension/FlightPlanAttributeContainer.h"

namespace Eurocat::Plugin
{
	class PluginAccess
	{
	public:
		static PluginAccess& Shared();
		static void SetupShared(std::shared_ptr<Plugin::EurocatPlugin> plugin);

		PluginAccess(std::shared_ptr<Plugin::EurocatPlugin> plugin);
		EurocatPlugin& GetPlugin();
		FlightPlanAttribute& FlightPlanAttribute(EuroScopePlugIn::CFlightPlan flightPlan);

	private:
		static std::shared_ptr<PluginAccess> shared;

		std::shared_ptr<Plugin::EurocatPlugin> plugin;
		std::unique_ptr<FlightPlanAttributeContainer> flightPlanAttributeContainer;
	};
}
