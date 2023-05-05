#pragma once

#include "warning/ICheckableDataProvider.h"
#include "warning/WarningTypes.h"

namespace Eurocat::Warning
{
	class DupeSquawkChecker
	{
	public:
		DupeSquawkChecker(std::shared_ptr<ICheckableDataProvider> dataProvider);
		void Check();
		std::vector<DupeWarning> GetWarnings();

	private:
		std::shared_ptr<ICheckableDataProvider> dataProvider;
		std::vector<DupeWarning> warnings;
		std::mutex m;
	};
}
