#pragma once

#include "pch.h"

#include "warning/ICheckableDataProvider.h"

namespace Eurocat::Warning
{
	class MockCheckableDataProvider : public ICheckableDataProvider
	{
	public:
		MOCK_METHOD(std::vector<CheckableRadarTarget>, GetRadarTargets, (), (override));
	};
}
