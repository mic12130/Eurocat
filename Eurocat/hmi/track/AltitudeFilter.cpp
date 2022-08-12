#include "base/pch.h"

#include "hmi/track/AltitudeFilter.h"

namespace Eurocat::Hmi::Track
{
	AltitudeFilter::AltitudeFilter(OptionData& option) : option(option)
	{
	}

	bool AltitudeFilter::InRange(IRadarTargetDataProvider& rt, Plugin::EurocatPlugin& plugin)
	{
		int altitude = rt.GetPressureAltitude();

		if (altitude > plugin.GetTransitionAltitude())
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
