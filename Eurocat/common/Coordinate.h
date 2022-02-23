#pragma once

namespace Eurocat::Common
{
	class Coordinate
	{
	public:
		Coordinate() : Coordinate(0, 0)
		{
		}

		Coordinate(double lat, double lon) : latitude(lat), longitude(lon)
		{
		}

		double latitude;
		double longitude;
	};
}
