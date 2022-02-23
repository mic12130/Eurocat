#pragma once

#include "pch.h"

#include "hmi/track/IAltitudeFilter.h"

namespace Eurocat::Hmi::Track
{
	class MockAltitudeFilter : public IAltitudeFilter
	{
	public:
		MOCK_METHOD(bool, InRange, (IRadarTargetDataProvider&, Plugin::PluginEnvironment&), (override));
	};
}
