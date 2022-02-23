#pragma once

#include "system/SystemService.h"
#include "plugin/PluginEnvironment.h"
#include "plugin/PluginEventManager.h"

namespace Eurocat::Plugin
{
	class PluginService : public System::SystemService
	{
	public:
		PluginService(
			std::shared_ptr<PluginEnvironment> pluginEnv,
			std::shared_ptr<PluginEventManager> pluginEventManager
		);
		PluginEnvironment& GetPluginEnvironment();
		PluginEventManager& GetPluginEventManager();
		void OnStart() override;
		void OnStop() override;

	private:
		std::shared_ptr<PluginEnvironment> pluginEnv;
		std::shared_ptr<PluginEventManager> pluginEventManager;
	};
}
