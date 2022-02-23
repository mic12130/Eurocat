#include "base/pch.h"

#include "plugin/PluginService.h"

#include "plugin/extension/FlightPlanAttributeUpdater.h"
#include "plugin/extension/FlightPlanProcessor.h"
#include "plugin/input/EuroScopeInputManager.h"
#include "plugin/input/EuroScopeInputBridge.h"
#include "plugin/PluginFunctionId.h"

using namespace Eurocat::Plugin::Extension;
using namespace Eurocat::Plugin::Input;

namespace Eurocat::Plugin
{
	PluginService::PluginService(
		std::shared_ptr<PluginEnvironment> pluginEnv,
		std::shared_ptr<PluginEventManager> pluginEventManager)
		: pluginEnv(std::move(pluginEnv)), pluginEventManager(std::move(pluginEventManager))
	{
	}

	PluginEnvironment& PluginService::GetPluginEnvironment()
	{
		return *pluginEnv;
	}

	PluginEventManager& PluginService::GetPluginEventManager()
	{
		return *pluginEventManager;
	}

	void PluginService::OnStart()
	{
		// The plugin itself is surely ready-to-go, so the only stuff need to be done here
		// is setting up those extension components of the plugin

		PluginEnvironment::SetShared(pluginEnv);
		PluginEventManager::SetShared(pluginEventManager);

		auto attributeUpdater = std::make_shared<FlightPlanAttributeUpdater>(*pluginEnv);
		pluginEventManager->AddFlightPlanEventHandler(attributeUpdater);
		pluginEventManager->AddTimedEventHandler(attributeUpdater);

		auto fpProcessor = std::make_shared<FlightPlanProcessor>(*pluginEnv);
		pluginEventManager->AddTimedEventHandler(fpProcessor);

		auto inputManager = std::make_shared<EuroScopeInputManager>(*pluginEnv);
		pluginEventManager->AddFunctionHandler(inputManager, PluginFunctionId::kSubmitInputFunctionId);
		EuroScopeInputBridge::shared->SetEuroScopeInputManager(inputManager);
	}

	void PluginService::OnStop()
	{
		PluginEnvironment::SetShared(nullptr);
		EuroScopeInputBridge::shared = nullptr;
	}
}
