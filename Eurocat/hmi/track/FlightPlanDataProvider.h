#pragma once

#include "hmi/track/IFlightPlanDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class FlightPlanDataProvider : public IFlightPlanDataProvider
	{
	public:
		FlightPlanDataProvider(EuroScopePlugIn::CFlightPlan& fp);
		CString GetCallsign() override;
		Hmi::FlightPlanDisplayState GetDisplayState() override;
		bool IsAcceptedReminding() override;
		CString GetAircraftType() override;
		CString GetOrigin() override;
		CString GetDestination() override;
		CString GetAlternate() override;
		CString GetRoute() override;
		CString GetArrivalRunway() override;
		std::optional<int> GetCfl() override;
		char GetWtc() override;
		std::vector<CString> GetWaypointsAhead(int preferredCount) override;
		Common::Coordinate GetFlightPlanTrackPosition()override;
		CTime GetLastStateUpdateTime() override;
		int GetRfl() override;
		bool IsCflAcknowledged() override;
		char GetCapabilities() override;
		CString GetFlightPlanType() override;
		CString GetLabelData() override;
		int GetAssignedHeading() override;
		int GetAssignedSpeed() override;
		int GetAssignedMach() override;
		CString GetAssignedSsr() override;
		CString GetPilotName() override;

	private:
		EuroScopePlugIn::CFlightPlan fp;
	};
}
