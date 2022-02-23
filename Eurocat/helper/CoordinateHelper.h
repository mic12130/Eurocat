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
	};
}
