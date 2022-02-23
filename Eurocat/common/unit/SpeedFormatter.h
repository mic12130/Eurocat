#pragma once

#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Common::Unit
{
	class SpeedFormatter
	{
	public:
		SpeedFormatter(Hmi::Unit::UnitDisplayMode unit);
		CString StringFromSpeed(int value);

	private:
		Hmi::Unit::UnitDisplayMode unit;

		const int kMaxImperialValue = 999;
		const int kMaxMetricValue = 9999;
	};
}
