#pragma once

#include "base/pch.h"

#include "plugin/Plugin.h"
#include "hmi/track/IRadarTargetDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class IAltitudeFilter
	{
	public:
		virtual ~IAltitudeFilter() = default;
		virtual bool InRange(IRadarTargetDataProvider& rt) = 0;
	};
}
