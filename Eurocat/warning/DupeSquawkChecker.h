#pragma once

#include "warning/IDupeSquawkCheckDataProvider.h"

namespace Eurocat::Warning
{
	class DupeSquawkChecker
	{
	public:
		DupeSquawkChecker(std::unique_ptr<IDupeSquawkCheckDataProvider> dataProvider);
		DupeSquawkChecker();
		void Check();
		std::vector<CString> GetWarningTargetIds();

	private:
		std::unique_ptr<IDupeSquawkCheckDataProvider> dataProvider;
		std::vector<CString> warningTargetIds;
	};
}
