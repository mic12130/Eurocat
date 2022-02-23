#pragma once

#include "hmi/track/IAltitudeFilter.h"
#include "hmi/track/option/OptionData.h"

namespace Eurocat::Hmi::Track
{
	class AltitudeFilter : public IAltitudeFilter
	{
	public:
		AltitudeFilter(OptionData& option);
		bool InRange(IRadarTargetDataProvider& rt, Plugin::PluginEnvironment& pluginEnv) override;
		bool InRange(int altitude);

	private:
		Plugin::PluginEnvironment& pluginEnv;
		OptionData& option;
	};
}
