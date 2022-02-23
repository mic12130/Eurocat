#include "base/pch.h"

#include "warning/WarningManager.h"

namespace Eurocat::Warning
{
	WarningManager& WarningManager::Shared()
	{
		return *shared;
	}

	void WarningManager::SetShared(std::shared_ptr<WarningManager> ptr)
	{
		if (ptr == nullptr)
		{
			shared = nullptr;
		}
		else
		{
			shared = std::move(ptr);
		}
	}

	WarningManager::WarningManager(
		std::shared_ptr<BuiltinWarningChecker> builtinWarningChecker,
		std::shared_ptr<DupeSquawkChecker> dupeSquawkChecker)
		: builtinWarningChecker(builtinWarningChecker),
		dupeSquawkChecker(dupeSquawkChecker)
	{
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
