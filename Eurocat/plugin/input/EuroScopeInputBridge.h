#pragma once

#include "plugin/input/EuroScopeInputManager.h"

namespace Eurocat::Plugin::Input
{
	class EuroScopeInputBridge
	{
	public:
		static std::unique_ptr<EuroScopeInputBridge> shared;

		void SetEuroScopeInputManager(std::shared_ptr<EuroScopeInputManager> manager);
		auto GetEuroScopeInputManager() -> std::weak_ptr<EuroScopeInputManager>;

	private:
		std::weak_ptr<EuroScopeInputManager> inputManager;
	};
}
