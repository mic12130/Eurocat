#pragma once

#include "pch.h"

#include "hmi/track/IFlightPlanDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class MockFlightPlanDataProvider : public IFlightPlanDataProvider
	{
	public:
		MOCK_METHOD(CString, GetCallsign, (), (override));
		MOCK_METHOD(Hmi::FlightPlanDisplayState, GetDisplayState, (), (override));
		MOCK_METHOD(bool, IsAcceptedReminding, (), (override));
		MOCK_METHOD(CTime, GetLastStateUpdateTime, (), (override));
		MOCK_METHOD(CString, GetAircraftType, (), (override));
		MOCK_METHOD(CString, GetDestination, (), (override));
		MOCK_METHOD(CString, GetArrivalRunway, (), (override));
		MOCK_METHOD(std::optional<int>, GetCfl, (), (override));
		MOCK_METHOD(int, GetRfl, (), (override));
		MOCK_METHOD(char, GetWtc, (), (override));
		MOCK_METHOD(std::vector<CString>, GetWaypointsAhead, (int), (override));
		MOCK_METHOD(Common::Coordinate, GetFlightPlanTrackPosition, (), (override));
		MOCK_METHOD(bool, IsCflAcknowledged, (), (override));
		MOCK_METHOD(char, GetCapabilities, (), (override));
		MOCK_METHOD(CString, GetFlightPlanType, (), (override));
		MOCK_METHOD(CString, GetLabelData, (), (override));
		MOCK_METHOD(int, GetAssignedHeading, (), (override));
		MOCK_METHOD(int, GetAssignedSpeed, (), (override));
		MOCK_METHOD(int, GetAssignedMach, (), (override));
		MOCK_METHOD(CString, GetPilotName, (), (override));
	};
}
