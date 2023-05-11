#pragma once

#include "warning/BuiltinWarningChecker.h"
#include "warning/DupeSquawkChecker.h"
#include "warning/CheckableDataProvider.h"
#include "warning/WarningData.h"
#include "plugin/ITimedEventHandler.h"
#include "config/ConfigEventManager.h"

namespace Eurocat::Plugin
{
	class PluginEventManager;
}

namespace Eurocat::Warning
{
	class WarningManager
		: public Plugin::ITimedEventHandler,
		public Config::IConfigEventHandler,
		public std::enable_shared_from_this<WarningManager>
	{
	public:
		WarningManager();
		~WarningManager();
		void SubscribeToPluginEvents(Plugin::PluginEventManager& manager);
		void SubscribeToConfigEvents(
			Config::ConfigCollection& config,
			Config::ConfigEventManager& manager);
		std::shared_ptr<WarningData> MakeWarningData();
		void OnTimedEvent(int counter) override;
		void OnConfigUpdate(Config::ConfigCollection& config) override;

	private:
		std::shared_ptr<CheckableDataProvider> dataProvider;
		std::shared_ptr<BuiltinWarningChecker> builtinWarningChecker;
		std::shared_ptr<DupeSquawkChecker> dupeSquawkChecker;
	};
}
