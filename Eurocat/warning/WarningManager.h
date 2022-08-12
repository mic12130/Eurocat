#pragma once

#include "warning/BuiltinWarningChecker.h"
#include "warning/DupeSquawkChecker.h"
#include "warning/RadarTargetWarningInfo.h"

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
		std::vector<CString> GetClamWarningTargetIds();
		std::vector<CString> GetRamWarningTargetIds();
		std::vector<CString> GetDupeWarningTargetIds();
		auto GetWarningInfoByTargetId(CString targetId) -> RadarTargetWarningInfo;

	private:
		std::shared_ptr<BuiltinWarningChecker> builtinWarningChecker;
		std::shared_ptr<DupeSquawkChecker> dupeSquawkChecker;

		inline static std::shared_ptr<WarningManager> shared = nullptr;
	};
}
