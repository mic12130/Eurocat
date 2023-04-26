#pragma once

#include "warning/BuiltinWarningChecker.h"
#include "warning/DupeSquawkChecker.h"

namespace Eurocat::Warning
{
	class WarningData
	{
	public:
		static WarningData& Shared();
		static void SetupShared(std::shared_ptr<WarningData> shared);

		WarningData(
			std::shared_ptr<BuiltinWarningChecker> builtinWarningChecker,
			std::shared_ptr<DupeSquawkChecker> dupeSquawkChecker);
		std::vector<BuiltinWarning> GetBuiltinWarnings();
		std::vector<DupeWarning> GetDupeWarnings();

	private:
		static std::shared_ptr<WarningData> shared;

		std::shared_ptr<BuiltinWarningChecker> builtinWarningChecker;
		std::shared_ptr<DupeSquawkChecker> dupeSquawkChecker;
	};
}