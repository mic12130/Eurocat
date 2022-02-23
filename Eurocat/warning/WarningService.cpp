#include "base/pch.h"

#include "warning/WarningService.h"

#include "plugin/PluginEventManager.h"
#include "warning/BuiltinWarningChecker.h"
#include "warning/DupeSquawkChecker.h"
#include "warning/DupeSquawkCheckScheduler.h"
#include "warning/WarningManager.h"

using namespace Eurocat::Plugin;

namespace Eurocat::Warning
{
	WarningService::WarningService()
	{
	}

	void WarningService::OnStart()
	{
		auto builtinWarningChecker = std::make_shared<BuiltinWarningChecker>();
		PluginEventManager::Shared().AddTimedEventHandler(builtinWarningChecker);

		auto dupeSquawkChecker = std::make_shared<DupeSquawkChecker>();
		auto dupeSquawkCheckScheduler = std::make_shared<DupeSquawkCheckScheduler>(dupeSquawkChecker);
		PluginEventManager::Shared().AddTimedEventHandler(dupeSquawkCheckScheduler);

		auto sharedWarningManager = std::make_shared<WarningManager>(
			builtinWarningChecker,
			dupeSquawkChecker
			);
		WarningManager::SetShared(sharedWarningManager);
	}

	void WarningService::OnStop()
	{
		WarningManager::SetShared(nullptr);
	}
}
