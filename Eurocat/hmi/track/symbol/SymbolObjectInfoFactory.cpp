#include "base/pch.h"

#include "hmi/track/symbol/SymbolObjectInfoFactory.h"

#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/TrackObjectId.h"
#include "external/CallsignLookup.h"

using namespace Eurocat::External;

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

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForCoupledTrack(
		IFlightPlanDataProvider& fp, IRadarTargetDataProvider& rt, const TrackProfile& profile)
	{
		CString msg;
		msg.Format("%s %s %s", GenerateFpSummaryMessage(fp), GenerateSsrMessage(fp, rt), GenerateFpDetailMessage(fp));
		return SymbolObjectInfo(TrackObjectId::Generate(profile.id, TrackObjectIdSuffix::kSymbol), msg);
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForFlightPlanTrack(IFlightPlanDataProvider& fp, const TrackProfile& profile)
	{
		CString msg;
		msg.Format("%s %s %s", GenerateFpSummaryMessage(fp), GenerateAssrOnlyMessage(fp), GenerateFpDetailMessage(fp));
		return SymbolObjectInfo(TrackObjectId::Generate(profile.id, TrackObjectIdSuffix::kSymbol), msg);
	}

	SymbolObjectInfo SymbolObjectInfoFactory::MakeForGroundTrack()
	{
		return { TrackObjectId::kNoActionObjectId, "Ground" };
	}

	CString SymbolObjectInfoFactory::GenerateFpSummaryMessage(IFlightPlanDataProvider& fp)
	{
		CString callsign = fp.GetCallsign();
		CString msg(callsign);

		if (auto radioCallsign = CallsignLookup::Shared().GetCallsign(callsign); radioCallsign.has_value())
		{
			msg += " ";
			msg += "(" + radioCallsign.value() + ")";
		}

		if (auto name = fp.GetPilotName(); name != "")
		{
			msg += " ";
			msg += "(" + fp.GetPilotName() + ")";
		}

		msg += ": ";
		msg += fp.GetAircraftType();

		return msg;
	}

	CString SymbolObjectInfoFactory::GenerateFpDetailMessage(IFlightPlanDataProvider& fp)
	{
		CString msg;
		msg += fp.GetOrigin();
		msg += "==>";
		msg += fp.GetDestination();

		if (auto altn = fp.GetAlternate(); altn != "")
		{
			msg += " ";
			msg += "(" + altn + ")";
		}

		msg += " ";
		msg += "at ";

		int rfl = fp.GetRfl();
		CString rflStr;
		if (rfl > transAlt)
			msg += "FL" + CString(std::to_string(rfl / 100).c_str());
		else
			msg += CString(std::to_string(rfl).c_str()) + " ft";

		msg += " ";
		msg += "Route: ";
		msg += fp.GetRoute();

		return msg;
	}

	CString SymbolObjectInfoFactory::GenerateSsrMessage(IFlightPlanDataProvider& fp, IRadarTargetDataProvider& rt)
	{
		CString assr = fp.GetAssignedSsr();
		CString ssr = rt.GetSsr();
		CString msg = fp.GetFlightPlanType() + ":" + ssr;

		if (assr != "" && assr != ssr)
		{
			msg += " ";
			msg += "(" + assr + ")";
		}

		return msg;
	}

	CString SymbolObjectInfoFactory::GenerateAssrOnlyMessage(IFlightPlanDataProvider& fp)
	{
		CString assr = fp.GetAssignedSsr();
		CString msg = fp.GetFlightPlanType() + ":----";

		if (assr != "")
		{
			msg += " ";
			msg += "(" + assr + ")";
		}

		return msg;
	}
}
