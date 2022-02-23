#pragma once

namespace Eurocat::Common::Unit
{
	class AltitudeConverter
	{
	public:
		static int MeterToFeet(int value);
		static int FeetToMeter(int value);
	};
}
