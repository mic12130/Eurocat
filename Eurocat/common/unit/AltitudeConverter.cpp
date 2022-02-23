#include "base/pch.h"

#include "common/unit/AltitudeConverter.h"

namespace Eurocat::Common::Unit
{
	int AltitudeConverter::MeterToFeet(int value)
	{
		return int(value / 0.3048 + 0.5);
	}

	int AltitudeConverter::FeetToMeter(int value)
	{
		return int(value * 0.3048 + 0.5);
	}
}
