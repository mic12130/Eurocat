#pragma once

#include "plugin/IFlightPlanEventHandler.h"
#include "plugin/IRadarTargetEventHandler.h"
#include "plugin/ITagItemProvider.h"
#include "plugin/IFunctionHandler.h"
#include "plugin/ITimedEventHandler.h"
#include "screen/IScreenEventHandler.h"

namespace Eurocat::Plugin
{
	class PluginEventManager
	{
	public:
		PluginEventManager(
			std::vector<std::shared_ptr<IFlightPlanEventHandler>>& flightPlanEventHandlers,
			std::vector<std::shared_ptr<IRadarTargetEventHandler>>& radarEventHandlers,
			std::vector<std::shared_ptr<ITimedEventHandler>>& timerEventHandlers,
			std::map<int, std::shared_ptr<ITagItemProvider>>& tagItemProviders,
			std::map<int, std::shared_ptr<IFunctionHandler>>& functionHandlers,
			std::vector<std::shared_ptr<Screen::IScreenEventHandler>>& screenEventHandlers
		);

		void AddFlightPlanEventHandler(std::shared_ptr<IFlightPlanEventHandler> handler);
		void AddRadarTargetEventHandler(std::shared_ptr<IRadarTargetEventHandler> handler);
		void AddTimedEventHandler(std::shared_ptr<ITimedEventHandler> handler);
		void AddTagItemProvider(std::shared_ptr<ITagItemProvider> provider, int code);
		void AddFunctionHandler(std::shared_ptr<IFunctionHandler> handler, int code);
		void AddScreenEventHandler(std::shared_ptr<Screen::IScreenEventHandler> handler);

	private:
		std::vector<std::shared_ptr<IFlightPlanEventHandler>>& flightPlanEventHandlers;
		std::vector<std::shared_ptr<IRadarTargetEventHandler>>& radarEventHandlers;
		std::vector<std::shared_ptr<ITimedEventHandler>>& timerEventHandlers;
		std::map<int, std::shared_ptr<ITagItemProvider>>& tagItemProviders;
		std::map<int, std::shared_ptr<IFunctionHandler>>& functionHandlers;
		std::vector<std::shared_ptr<Screen::IScreenEventHandler>>& screenEventHandlers;
	};
}
