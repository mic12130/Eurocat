#pragma once

#include "hmi/track/symbol/SymbolObjectInfo.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/profile/TrackProfile.h"

namespace Eurocat::Hmi::Track
{
	class SymbolObjectInfoFactory
	{
	public:
		SymbolObjectInfo MakeForPsrTrack();
		SymbolObjectInfo MakeForUncoupledTrack(const TrackProfile& profile);
		SymbolObjectInfo MakeForCoupledTrack(IFlightPlanDataProvider& fp, const TrackProfile& profile);
		SymbolObjectInfo MakeForFlightPlanTrack(IFlightPlanDataProvider& fp, const TrackProfile& profile);
		SymbolObjectInfo MakeForGroundTrack();
	};
}
