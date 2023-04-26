#pragma once

#include "hmi/track/IAltitudeFilter.h"
#include "hmi/track/option/OptionData.h"

namespace Eurocat::Hmi::Track
{
	class AltitudeFilter : public IAltitudeFilter
	{
	public:
		AltitudeFilter(OptionData& option, int transAltitude);
		bool InRange(IRadarTargetDataProvider& rt) override;
		bool InRange(int altitude);

	private:
		OptionData& option;

		// We use this to correct the altitude from radar target
		// It will not take any effect when InRange(int altitude) variant is called
		int transAltitude;
	};
}
