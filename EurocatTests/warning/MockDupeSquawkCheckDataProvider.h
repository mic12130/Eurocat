#pragma once

#include "pch.h"

#include "warning/IDupeSquawkCheckDataProvider.h"

namespace Eurocat::Warning
{
	class MockDupeSquawkCheckDataProvider : public IDupeSquawkCheckDataProvider
	{
	public:
		MOCK_METHOD(std::vector<SquawkData>, GetSquawkDataCollection, (), (override));
	};
}
