#pragma once

#include "warning/BuiltinWarningChecker.h"
#include "warning/DupeSquawkChecker.h"
#include "warning/WarningData.h"

namespace Eurocat::Plugin
{
	class PluginEventManager;
}

namespace Eurocat::Warning
{
	class WarningManager
	{
	public:
		WarningManager();
		void SubscribeToPluginEvents(Plugin::PluginEventManager& manager);
		std::shared_ptr<WarningData> MakeWarningData();

	private:
		std::shared_ptr<BuiltinWarningChecker> builtinWarningChecker;
		std::shared_ptr<DupeSquawkChecker> dupeSquawkChecker;
	};
}
