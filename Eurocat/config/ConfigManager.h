#pragma once

#include "config/ConfigCollection.h"
#include "config/ConfigEventManager.h"

namespace Eurocat::Config
{
	class ConfigManager
	{
	public:
		ConfigManager();
		void Load();
		ConfigCollection MakeConfigCollection();
		ConfigEventManager& GetEventManager();

	private:
		std::shared_ptr<SettingsData> settingsData;
		std::unique_ptr<ConfigEventManager> eventManager;
		std::vector<std::shared_ptr<IConfigEventHandler>> eventHandlers;
	};
}