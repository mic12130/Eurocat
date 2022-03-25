#pragma once

#include "base/pch.h"

#include "common/Coordinate.h"
#include "common/FlightPlanState.h"
#include "hmi/FlightPlanDisplayState.h"

namespace Eurocat::Hmi::Track
{
	class IFlightPlanDataProvider
	{
	public:
		virtual ~IFlightPlanDataProvider() = default;
		virtual CString GetCallsign() = 0;
		virtual Hmi::FlightPlanDisplayState GetDisplayState() = 0;
		virtual bool IsAcceptedReminding() = 0;
		virtual CTime GetLastStateUpdateTime() = 0;
		virtual CString GetAircraftType() = 0;
		virtual CString GetDestination() = 0;
		virtual CString GetArrivalRunway() = 0;
		virtual std::optional<int> GetCfl() = 0;
		virtual int GetRfl() = 0;
		virtual char GetWtc() = 0;
		virtual std::vector<CString> GetWaypointsAhead(int preferredCount) = 0;
		virtual Common::Coordinate GetFlightPlanTrackPosition() = 0;
		virtual bool IsCflAcknowledged() = 0;
		virtual char GetCapabilities() = 0;
		virtual CString GetFlightPlanType() = 0;
		virtual CString GetLabelData() = 0;
		virtual int GetAssignedHeading() = 0;
		virtual int GetAssignedSpeed() = 0;
		virtual int GetAssignedMach() = 0;
	};
}
