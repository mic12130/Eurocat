#pragma once

#include "base/pch.h"

#include "common/Coordinate.h"

namespace Eurocat::Helper
{
	class CoordinateHelper
	{
	public:
		static EuroScopePlugIn::CPosition ConvertToCPosition(Common::Coordinate coord)
		{
			EuroScopePlugIn::CPosition result;
			result.m_Latitude = coord.latitude;
			result.m_Longitude = coord.longitude;

			return result;
		}

		static Common::Coordinate ConvertToPosition(EuroScopePlugIn::CPosition pos)
		{
			return Common::Coordinate(pos.m_Latitude, pos.m_Longitude);
		}

		static double Distance(Common::Coordinate origin, Common::Coordinate dest)
		{
			EuroScopePlugIn::CPosition _origin = ConvertToCPosition(origin);
			EuroScopePlugIn::CPosition _dest = ConvertToCPosition(dest);

			return _origin.DistanceTo(_dest);
		}

		static double Direction(Common::Coordinate origin, Common::Coordinate dest)
		{
			EuroScopePlugIn::CPosition _origin = ConvertToCPosition(origin);
			EuroScopePlugIn::CPosition _dest = ConvertToCPosition(dest);

			return _origin.DirectionTo(_dest);
		}

		static double DistanceToLine(Common::Coordinate origin, Common::Coordinate p1, Common::Coordinate p2)
		{
			double l1 = Distance(p1, p2);
			double l2 = Distance(origin, p1);
			double l3 = Distance(origin, p2);
			double p = (l1 + l2 + l3) / 2;
			double s = sqrt(p * (p - l1) * (p - l2) * (p - l3));

			return s * 2 / l1;
		}
	};
}
