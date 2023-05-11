#include "base/pch.h"

#include "warning/WarningManager.h"
#include "plugin/PluginEventManager.h"

std::atomic<bool> runCheckerThread = true;

namespace Eurocat::Warning
{
	WarningManager::WarningManager()
	{
		dataProvider = std::make_shared<CheckableDataProvider>();
		builtinWarningChecker = std::make_shared<BuiltinWarningChecker>();
		dupeSquawkChecker = std::make_shared<DupeSquawkChecker>(dataProvider);

		std::thread checkerThread([&]()
			{
				while (runCheckerThread)
				{
					std::this_thread::sleep_for(std::chrono::seconds(1));
					spdlog::info("Start running warning checks");
					dupeSquawkChecker->Check();
					spdlog::info("Finished warning checks");
				}
			});
		checkerThread.detach();
	}

	WarningManager::~WarningManager()
	{
		runCheckerThread = false;
	}

	void WarningManager::SubscribeToPluginEvents(Plugin::PluginEventManager& manager)
	{
		manager.AddTimedEventHandler(shared_from_this());
	}

	void WarningManager::SubscribeToConfigEvents(Config::ConfigCollection& config, Config::ConfigEventManager& manager)
	{
		manager.AddConfigEventHandler(shared_from_this());
		OnConfigUpdate(config);
	}

	std::shared_ptr<WarningData> WarningManager::MakeWarningData()
	{
		return std::make_shared<WarningData>(builtinWarningChecker, dupeSquawkChecker);
	}

	void WarningManager::OnTimedEvent(int counter)
	{
		dataProvider->UpdateFromPlugin();
		builtinWarningChecker->Check();
	}

	void WarningManager::OnConfigUpdate(Config::ConfigCollection& config)
	{
	}
}
