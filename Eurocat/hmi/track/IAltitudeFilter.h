#pragma once

#include "base/pch.h"

#include "plugin/PluginEnvironment.h"
#include "hmi/track/IRadarTargetDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class IAltitudeFilter
	{
	public:
		virtual ~IAltitudeFilter() = default;
		virtual bool InRange(IRadarTargetDataProvider& rt, Plugin::PluginEnvironment& pluginEnv) = 0;
	};
}
