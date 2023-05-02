#include "base/pch.h"

#include "config/ConfigManager.h"

#include "helper/FilesystemHelper.h"

namespace Eurocat::Config
{
	ConfigManager::ConfigManager()
	{
		eventManager = std::make_unique<ConfigEventManager>(eventHandlers);
	}

	void ConfigManager::Load()
	{
		namespace fs = std::filesystem;

		auto dir = fs::path(FilesystemHelper::GetDllDirPath()).append("Eurocat_configs");

		// Parse Settings.txt
		auto settingsStorage = SettingsStorage();
		settingsStorage.Load(dir.append("Settings.txt").string());
		settingsData = std::make_shared<SettingsData>(settingsStorage);

		// Notify event handlers
		auto configCollection = MakeConfigCollection();
		
		for (auto& handler : eventHandlers)
		{
			handler->OnConfigUpdate(configCollection);
		}
	}

	ConfigCollection ConfigManager::MakeConfigCollection()
	{
		return ConfigCollection(*settingsData);
	}

	ConfigEventManager& ConfigManager::GetEventManager()
	{
		return *eventManager;
	}
}