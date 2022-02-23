#pragma once

#include "base/pch.h"

#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/IRadarTargetDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class AltFilterOverrideCheck
	{
	public:
		static bool CheckForUncoupledTrack(IRadarTargetDataProvider& rt)
		{
			// TODO: Check alerts

			if (IsEmergency(rt))
			{
				return true;
			}

			return false;
		}

		static bool CheckForCoupledTrack(IRadarTargetDataProvider& rt, IFlightPlanDataProvider& fp)
		{
			auto state = fp.GetDisplayState();

			// TODO: Check alerts

			if (IsEmergency(rt))
			{
				return true;
			}

			if (state == Hmi::FlightPlanDisplayState::Announced ||
				state == Hmi::FlightPlanDisplayState::HandOverIn ||
				state == Hmi::FlightPlanDisplayState::HandOverOut ||
				state == Hmi::FlightPlanDisplayState::Jurisdiction)
			{
				return true;
			}

			return false;
		}

	private:
		static bool IsEmergency(IRadarTargetDataProvider& rt)
		{
			CString ssr = rt.GetSsr();
			return ssr == "7500" || ssr == "7600" || ssr == "7700";
		}
	};
}
