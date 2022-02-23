#include "base/pch.h"

#include "common/unit/AltitudeFormatter.h"

namespace Eurocat::Common::Unit
{
	AltitudeFormatter::AltitudeFormatter(Hmi::Unit::UnitDisplayMode unit) : unit(unit)
	{
	}

	CString AltitudeFormatter::StringFromAltitude(int value)
	{
		int fixedValue = value;
		CString str;

		if (value < 0)
		{
			fixedValue = 0;
		}
		else if (value > kMaxValue)
		{
			fixedValue = kMaxValue;
		}

		if (unit == Hmi::Unit::UnitDisplayMode::Imperial)
		{
			str.Format("%03d", fixedValue / 100);
		}
		else if (unit == Hmi::Unit::UnitDisplayMode::Metric)
		{
			str.Format("%04d", fixedValue / 10);
		}

		return str;
	}
}
