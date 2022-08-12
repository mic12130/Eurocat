#include "base/pch.h"

#include "system/SystemManager.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Warning;
using namespace Eurocat::Hmi;
using namespace Eurocat::TagItem;

namespace Eurocat
{
	std::shared_ptr<SystemManager> SystemManager::shared = std::shared_ptr<SystemManager>(new SystemManager());

	SystemManager& SystemManager::Shared()
	{
		return *shared;
	}

	void SystemManager::Startup()
	{
		// In this period, do not access the shared instance of system manager,
		// because we cannot ensure the components to be accessed have been initialized

		plugin = std::make_shared<EurocatPlugin>();

		warningManager = std::make_shared<WarningManager>();
		warningManager->SubscribeToPluginEvents(*plugin->GetEventManager());

		hmiManager = std::make_shared<HmiManager>();
		hmiManager->SubscribeToPluginEvents(*plugin->GetEventManager());

		tagItemManager = std::make_shared<TagItemManager>(hmiManager->GetUnitDisplayManager());
		tagItemManager->SubscribeToPluginEvents(*plugin->GetEventManager());
		tagItemManager->RegisterItems(*plugin);
	}

	void SystemManager::Cleanup()
	{
	}

	Plugin::EurocatPlugin& SystemManager::GetPlugin() const
	{
		return *plugin;
	}

	std::shared_ptr<WarningManager> SystemManager::GetWarningManager() const
	{
		return warningManager;
	}
}
