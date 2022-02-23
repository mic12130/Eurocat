#include "base/pch.h"

#include "plugin/input/EuroScopeInputBridge.h"

namespace Eurocat::Plugin::Input
{
	std::unique_ptr<EuroScopeInputBridge> EuroScopeInputBridge::shared = std::make_unique<EuroScopeInputBridge>();

	void EuroScopeInputBridge::SetEuroScopeInputManager(std::shared_ptr<EuroScopeInputManager> manager)
	{
		inputManager = manager;
	}

	auto EuroScopeInputBridge::GetEuroScopeInputManager() -> std::weak_ptr<EuroScopeInputManager>
	{
		return inputManager;
	}
}
