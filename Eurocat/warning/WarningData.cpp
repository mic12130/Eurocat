#include "base/pch.h"

#include "warning/WarningData.h"

namespace Eurocat::Warning
{
	std::shared_ptr<WarningData> WarningData::shared = nullptr;

	WarningData& WarningData::Shared()
	{
		return *shared;
	}

	void WarningData::SetupShared(std::shared_ptr<WarningData> shared)
	{
		WarningData::shared = std::move(shared);
	}

	WarningData::WarningData(
		std::shared_ptr<BuiltinWarningChecker> builtinWarningChecker,
		std::shared_ptr<DupeSquawkChecker> dupeSquawkChecker)
		: builtinWarningChecker(builtinWarningChecker),
		dupeSquawkChecker(dupeSquawkChecker)
	{
	}

	std::vector<BuiltinWarning> WarningData::GetBuiltinWarnings()
	{
		return builtinWarningChecker->GetWarnings();
	}

	std::vector<DupeWarning> WarningData::GetDupeWarnings()
	{
		return dupeSquawkChecker->GetWarnings();
	}
}