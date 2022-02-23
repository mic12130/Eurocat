#pragma once

#include "warning/SquawkData.h"

namespace Eurocat::Warning
{
	class IDupeSquawkCheckDataProvider
	{
	public:
		virtual ~IDupeSquawkCheckDataProvider() = default;
		virtual std::vector<SquawkData> GetSquawkDataCollection() = 0;
	};
}
