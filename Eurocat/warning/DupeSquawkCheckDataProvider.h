#pragma once

#include "warning/IDupeSquawkCheckDataProvider.h"

namespace Eurocat::Warning
{
	class DupeSquawkCheckDataProvider : public IDupeSquawkCheckDataProvider
	{
	public:
		std::vector<SquawkData> GetSquawkDataCollection() override;
	};
}
