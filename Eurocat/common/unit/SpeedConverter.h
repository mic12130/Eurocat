#pragma once

namespace Eurocat::Common::Unit
{
	class SpeedConverter
	{
	public:
		static int KphToKnot(int value);
		static int KnotToKph(int value);
	};
}
