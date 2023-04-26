#include "base/pch.h"

#include "warning/WarningManager.h"
#include "warning/DupeSquawkCheckScheduler.h"
#include "plugin/PluginEventManager.h"

namespace Eurocat::Warning
{
	WarningManager::WarningManager()
	{
		builtinWarningChecker = std::make_shared<BuiltinWarningChecker>();
		dupeSquawkChecker = std::make_shared<DupeSquawkChecker>();
	}

	void WarningManager::SubscribeToPluginEvents(Plugin::PluginEventManager& manager)
	{
		auto dupeSquawkCheckScheduler = std::make_shared<DupeSquawkCheckScheduler>(dupeSquawkChecker);
		manager.AddTimedEventHandler(builtinWarningChecker);
		manager.AddTimedEventHandler(dupeSquawkCheckScheduler);
	}

	std::shared_ptr<WarningData> WarningManager::MakeWarningData()
	{
		return std::make_shared<WarningData>(builtinWarningChecker, dupeSquawkChecker);
	}
}
