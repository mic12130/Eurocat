#pragma once

#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Common::Unit
{
	class AltitudeFormatter
	{
	public:
		AltitudeFormatter(Hmi::Unit::UnitDisplayMode unit);
		CString StringFromAltitude(int value);

	private:
		Hmi::Unit::UnitDisplayMode unit;

		const int kMaxValue = 99999;
	};
}
