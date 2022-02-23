#pragma once

#include "base/pch.h"

#include "common/Coordinate.h"

namespace Eurocat::Hmi::Track
{
	class IRadarTargetDataProvider
	{
	public:
		virtual ~IRadarTargetDataProvider() = default;
		virtual int GetGroundSpeed() = 0;
		virtual int GetPressureAltitude() = 0;
		virtual int GetFlightLevel() = 0;
		virtual double GetHeading() = 0;
		virtual CString GetSsr() = 0;
		virtual CString GetTargetId() = 0;
		virtual int GetVerticalSpeed() = 0;
		virtual bool IsModeI() = 0;
		virtual Common::Coordinate GetPosition() = 0;
		virtual std::vector<int> GetHistoricalGroundSpeeds(int preferredCount) = 0;
		virtual std::vector<Common::Coordinate> GetHistoricalPositions(int preferredCount) = 0;
	};
}
