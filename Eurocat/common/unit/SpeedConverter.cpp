#include "base/pch.h"

#include "common/unit/SpeedConverter.h"

namespace Eurocat::Common::Unit
{
	int SpeedConverter::KphToKnot(int value)
	{
		return int(value / 1.852 + 0.5);
	}
	int SpeedConverter::KnotToKph(int value)
	{
		return int(value * 1.852 + 0.5);
	}
}
