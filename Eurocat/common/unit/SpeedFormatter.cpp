#include "base/pch.h"

#include "common/unit/SpeedFormatter.h"

namespace Eurocat::Common::Unit
{
	SpeedFormatter::SpeedFormatter(Hmi::Unit::UnitDisplayMode unit) : unit(unit)
	{
	}

	CString SpeedFormatter::StringFromSpeed(int value)
	{
		int fixedValue = value;
		CString str;


		if (value < 0)
		{
			fixedValue = 0;
		}

		if (unit == Hmi::Unit::UnitDisplayMode::Imperial)
		{
			if (value > kMaxImperialValue)
			{
				fixedValue = kMaxImperialValue;
			}

			str.Format("%02d", fixedValue / 10);
		}
		else if (unit == Hmi::Unit::UnitDisplayMode::Metric)
		{
			if (value > kMaxMetricValue)
			{
				fixedValue = kMaxMetricValue;
			}

			str.Format("%03d", fixedValue / 10);
		}

		return str;
	}
}
