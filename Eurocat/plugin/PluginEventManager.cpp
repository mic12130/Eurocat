#include "base/pch.h"

#include "plugin/PluginEventManager.h"

namespace Eurocat::Plugin
{
	PluginEventManager::PluginEventManager(
		std::vector<std::shared_ptr<IFlightPlanEventHandler>>& flightPlanEventHandlers,
		std::vector<std::shared_ptr<IRadarTargetEventHandler>>& radarEventHandlers,
		std::vector<std::shared_ptr<ITimedEventHandler>>& timerEventHandlers,
		std::map<int, std::shared_ptr<ITagItemProvider>>& tagItemProviders,
		std::map<int, std::shared_ptr<IFunctionHandler>>& functionHandlers,
		std::vector<std::shared_ptr<Screen::IScreenEventHandler>>& screenEventHandlers)
		: flightPlanEventHandlers(flightPlanEventHandlers),
		radarEventHandlers(radarEventHandlers),
		timerEventHandlers(timerEventHandlers),
		tagItemProviders(tagItemProviders),
		functionHandlers(functionHandlers),
		screenEventHandlers(screenEventHandlers)
	{
	}

	void PluginEventManager::AddFlightPlanEventHandler(const std::shared_ptr<IFlightPlanEventHandler> handler)
	{
		flightPlanEventHandlers.push_back(handler);
	}

	void PluginEventManager::AddRadarTargetEventHandler(const std::shared_ptr<IRadarTargetEventHandler> handler)
	{
		radarEventHandlers.push_back(handler);
	}

	void PluginEventManager::AddTimedEventHandler(std::shared_ptr<ITimedEventHandler> handler)
	{
		timerEventHandlers.push_back(handler);
	}

	void PluginEventManager::AddTagItemProvider(const std::shared_ptr<ITagItemProvider> provider, int code)
	{
		tagItemProviders[code] = provider;
	}

	void PluginEventManager::AddFunctionHandler(const std::shared_ptr<IFunctionHandler> handler, int code)
	{
		functionHandlers[code] = handler;
	}

	void PluginEventManager::AddScreenEventHandler(std::shared_ptr<Screen::IScreenEventHandler> handler)
	{
		screenEventHandlers.push_back(handler);
	}
}
