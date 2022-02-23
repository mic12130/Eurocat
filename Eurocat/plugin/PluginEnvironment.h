#pragma once

#include "plugin/extension/FlightPlanAttribute.h"

namespace Eurocat::Plugin
{
	class PluginEnvironment
	{
	public:
		static PluginEnvironment& Shared();
		static void SetShared(std::shared_ptr<PluginEnvironment> ptr);

		PluginEnvironment(EuroScopePlugIn::CPlugIn& plugin);
		Extension::FlightPlanAttribute& AttributeForFlightPlan(EuroScopePlugIn::CFlightPlan flightPlan);
		EuroScopePlugIn::CPlugIn& GetPlugin();

		static PluginEnvironment CreateDummy();

	private:
		inline static std::shared_ptr<PluginEnvironment> shared = nullptr;

		EuroScopePlugIn::CPlugIn& plugin;
		std::map<CString, Extension::FlightPlanAttribute> flightPlanAttributeMap;
	};
}
