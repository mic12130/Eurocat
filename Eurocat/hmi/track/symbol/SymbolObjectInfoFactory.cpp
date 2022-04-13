#include "base/pch.h"

#include "hmi/track/symbol/SymbolObjectInfoFactory.h"

#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/TrackObjectId.h"

namespace Eurocat::Hmi::Track
{
	SymbolObjectInfo SymbolObjectInfoFactory::MakeForPsrTrack()
	{
		return { TrackObjectId::kNoActionObjectId, "" };
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForUncoupledTrack(const TrackProfile& profile)
	{
		return SymbolObjectInfo(TrackObjectId::Generate(profile.id, TrackObjectIdSuffix::kSymbol), "Uncoupled");
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForCoupledTrack(IFlightPlanDataProvider& fp, const TrackProfile& profile)
	{
		CString msg;
		CString pilotName = "No Name";

		if (CString fetchedPilotName = fp.GetPilotName(); !fetchedPilotName.IsEmpty())
		{
			pilotName = fetchedPilotName;
		}

		msg.Format("%s (%s) (%s)", fp.GetCallsign(), "Callsign", pilotName.GetString());
		return SymbolObjectInfo(TrackObjectId::Generate(profile.id, TrackObjectIdSuffix::kSymbol), msg);
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForFlightPlanTrack(IFlightPlanDataProvider& fp, const TrackProfile& profile)
	{
		CString msg;
		CString pilotName = "No Name";

		if (CString fetchedPilotName = fp.GetPilotName(); !fetchedPilotName.IsEmpty())
		{
			pilotName = fetchedPilotName;
		}

		msg.Format("%s (%s) (%s)", fp.GetCallsign(), "Callsign", pilotName.GetString());
		return SymbolObjectInfo(TrackObjectId::Generate(profile.id, TrackObjectIdSuffix::kSymbol), msg);
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForGroundTrack()
	{
		return { TrackObjectId::kNoActionObjectId, "Ground" };
	}
}
