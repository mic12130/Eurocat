#pragma once

#include "system/SystemService.h"
#include "plugin/PluginService.h"

namespace Eurocat::System
{
	class SystemServiceManager
	{
	public:
		void StartPluginService(std::unique_ptr<Plugin::PluginService> service);
		void StartOtherServices();
		void StopServices();

	private:
		// Service related to the plugin itself and its extension components
		//
		// This is and will always be the only service not in the services vector
		// due to its specificity - having the same lifetime with the system and
		// impossible to be stopped or removed
		std::unique_ptr<Plugin::PluginService> pluginService;

		std::vector<std::shared_ptr<SystemService>> services;

		// Services that have the shortest lifecycle. This ensures they can
		// always safely access the resources of other services
		std::vector<std::shared_ptr<SystemService>> priorityServices;
	};
}
