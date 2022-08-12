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

	std::vector<CString> WarningManager::GetClamWarningTargetIds()
	{
		return builtinWarningChecker->GetClamWarningTargetIds();
	}

	std::vector<CString> WarningManager::GetRamWarningTargetIds()
	{
		return builtinWarningChecker->GetRamWarningTargetIds();
	}

	std::vector<CString> WarningManager::GetDupeWarningTargetIds()
	{
		return dupeSquawkChecker->GetWarningTargetIds();
	}

	auto WarningManager::GetWarningInfoByTargetId(CString targetId) -> RadarTargetWarningInfo
	{
		std::vector<CString> clamTargetIds = builtinWarningChecker->GetClamWarningTargetIds();
		std::vector<CString> ramTargetIds = builtinWarningChecker->GetRamWarningTargetIds();
		std::vector<CString> dupeTargetIds = dupeSquawkChecker->GetWarningTargetIds();

		RadarTargetWarningInfo result;
		result.isClam = std::find(clamTargetIds.begin(), clamTargetIds.end(), targetId) != clamTargetIds.end();
		result.isRam = std::find(ramTargetIds.begin(), ramTargetIds.end(), targetId) != ramTargetIds.end();
		result.isDupe = std::find(dupeTargetIds.begin(), dupeTargetIds.end(), targetId) != dupeTargetIds.end();
		return result;
	}
}
