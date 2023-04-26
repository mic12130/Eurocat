#pragma once

#include "warning/IDupeSquawkCheckDataProvider.h"
#include "warning/WarningTypes.h"

namespace Eurocat::Warning
{
	class DupeSquawkChecker
	{
	public:
		DupeSquawkChecker(std::shared_ptr<IDupeSquawkCheckDataProvider> dataProvider);
		DupeSquawkChecker();
		void Check();
		std::vector<DupeWarning> GetWarnings();

	private:
		std::shared_ptr<IDupeSquawkCheckDataProvider> dataProvider;
		std::vector<DupeWarning> warnings;
	};
}
