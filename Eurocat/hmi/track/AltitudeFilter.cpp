#include "base/pch.h"

#include "hmi/track/AltitudeFilter.h"

namespace Eurocat::Hmi::Track
{
	AltitudeFilter::AltitudeFilter(OptionData& option, int transAltitude)
		: option(option), transAltitude(transAltitude)
	{
	}

	bool AltitudeFilter::InRange(IRadarTargetDataProvider& rt)
	{
		int altitude = rt.GetPressureAltitude();

		if (altitude > transAltitude)
		{
			altitude = rt.GetFlightLevel();
		}

		return InRange(altitude);
	}

	bool AltitudeFilter::InRange(int altitude)
	{
		if (option.altitudeFilterLow != -1 && altitude < option.altitudeFilterLow)
		{
			return false;
		}

		if (option.altitudeFilterHigh != -1 && altitude > option.altitudeFilterHigh)
		{
			return false;
		}

		return true;
	}
}
