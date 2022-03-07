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
		return SymbolObjectInfo(TrackObjectId::Generate(profile.id, TrackObjectIdSuffix::kSymbol), "");
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForCoupledTrack(EuroScopePlugIn::CFlightPlan& fp, const TrackProfile& profile)
	{
		CString msg;
		CString pilotName = "No Name";

		if (fp.IsValid())
		{
			if (CString fetchedPilotName = fp.GetPilotName(); !fetchedPilotName.IsEmpty())
			{
				pilotName = fetchedPilotName;
			}
		}

		msg.Format("%s (%s) (%s)", fp.GetCallsign(), "Callsign", pilotName.GetString());
		return SymbolObjectInfo(TrackObjectId::Generate(profile.id, TrackObjectIdSuffix::kSymbol), msg);
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForFlightPlanTrack(EuroScopePlugIn::CFlightPlan& fp, const TrackProfile& profile)
	{
		CString msg;
		CString pilotName = "No Name";

		if (fp.IsValid())
		{
			if (CString fetchedPilotName = fp.GetPilotName(); !fetchedPilotName.IsEmpty())
			{
				pilotName = fetchedPilotName;
			}
		}

		msg.Format("%s (%s) (%s)", fp.GetCallsign(), "Callsign", pilotName.GetString());
		return SymbolObjectInfo(TrackObjectId::Generate(profile.id, TrackObjectIdSuffix::kSymbol), msg);
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForGroundTrack(EuroScopePlugIn::CRadarTarget& rt)
	{
		CString msg;
		CString pilotName = "No Name";
		auto fp = rt.GetCorrelatedFlightPlan();

		if (fp.IsValid())
		{
			if (CString fetchedPilotName = fp.GetPilotName(); !fetchedPilotName.IsEmpty())
			{
				pilotName = fetchedPilotName;
			}
		}
		
		msg.Format("%s (%s) (%s) [GROUND]", rt.GetCallsign(), "Callsign", pilotName.GetString());
		return { TrackObjectId::kNoActionObjectId, msg };
	}
}
