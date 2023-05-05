#pragma once

#include "warning/WarningTypes.h"

namespace Eurocat::Warning
{
	class BuiltinWarningChecker
	{
	public:
		void Check();
		std::vector<BuiltinWarning> GetWarnings();

	private:
		std::vector<BuiltinWarning> warnings;
	};
}
