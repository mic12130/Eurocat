#pragma once

#include "pch.h"

#include "hmi/track/IRadarTargetDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class MockRadarTargetDataProvider : public IRadarTargetDataProvider
	{
	public:
		MOCK_METHOD(int, GetGroundSpeed, (), (override));
		MOCK_METHOD(int, GetPressureAltitude, (), (override));
		MOCK_METHOD(int, GetFlightLevel, (), (override));
		MOCK_METHOD(double, GetHeading, (), (override));
		MOCK_METHOD(CString, GetSsr, (), (override));
		MOCK_METHOD(CString, GetTargetId, (), (override));
		MOCK_METHOD(int, GetVerticalSpeed, (), (override));
		MOCK_METHOD(bool, IsModeI, (), (override));
		MOCK_METHOD(Common::Coordinate, GetPosition, (), (override));
		MOCK_METHOD(std::vector<int>, GetHistoricalGroundSpeeds, (int), (override));
		MOCK_METHOD(std::vector<Common::Coordinate>, GetHistoricalPositions, (int), (override));
	};
}
