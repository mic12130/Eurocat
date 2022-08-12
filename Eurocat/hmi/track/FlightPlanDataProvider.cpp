#include "base/pch.h"

#include "hmi/track/FlightPlanDataProvider.h"

#include "helper/CoordinateHelper.h"
#include "hmi/FlightPlanDisplayStateGenerator.h"
#include "plugin/extension/FlightPlanExtension.h"

using namespace Eurocat::Hmi;
using namespace Eurocat::Common;
using namespace Eurocat::Plugin;

namespace Eurocat::Hmi::Track
{
	FlightPlanDataProvider::FlightPlanDataProvider(EuroScopePlugIn::CFlightPlan& fp) : fp(fp)
	{
	}

	CString FlightPlanDataProvider::GetCallsign()
	{
		return fp.GetCallsign();
	}

	Hmi::FlightPlanDisplayState FlightPlanDataProvider::GetDisplayState()
	{
		return FlightPlanDisplayStateGenerator::Generate(fp);
	}

	bool FlightPlanDataProvider::IsAcceptedReminding()
	{
		return FlightPlanDisplayStateGenerator::IsAcceptedReminding(fp);
	}

	CString FlightPlanDataProvider::GetAircraftType()
	{
		return fp.GetFlightPlanData().GetAircraftFPType();
	}

	CString FlightPlanDataProvider::GetDestination()
	{
		return fp.GetFlightPlanData().GetDestination();
	}

	CString FlightPlanDataProvider::GetArrivalRunway()
	{
		return fp.GetFlightPlanData().GetArrivalRwy();
	}

	std::optional<int> FlightPlanDataProvider::GetCfl()
	{
		return FlightPlanExtension(fp).GetCfl();
	}

	char FlightPlanDataProvider::GetWtc()
	{
		return fp.GetFlightPlanData().GetAircraftWtc();
	}

	std::vector<CString> FlightPlanDataProvider::GetWaypointsAhead(int preferredCount)
	{
		auto route = fp.GetExtractedRoute();
		std::vector<CString> result;

		for (int i = 0; i < route.GetPointsNumber(); i++)
		{
			// Continue if the waypoint has been passed
			if (route.GetPointDistanceInMinutes(i) == -1)
			{
				continue;
			}

			if (CString name = route.GetPointName(i); name != fp.GetFlightPlanData().GetDestination())
			{
				result.push_back(name);
			}
			else
			{
				break;
			}

			if (result.size() == preferredCount)
			{
				break;
			}
		}

		return result;
	}

	Common::Coordinate FlightPlanDataProvider::GetFlightPlanTrackPosition()
	{
		return Helper::CoordinateHelper::ConvertToPosition(fp.GetFPTrackPosition().GetPosition());
	}

	CTime FlightPlanDataProvider::GetLastStateUpdateTime()
	{
		return FlightPlanExtension(fp).GetLastStateUpdateTime();
	}

	int FlightPlanDataProvider::GetRfl()
	{
		return fp.GetFinalAltitude();
	}

	bool FlightPlanDataProvider::IsCflAcknowledged()
	{
		return FlightPlanExtension(fp).GetCflAcknowledged();
	}

	char FlightPlanDataProvider::GetCapabilities()
	{
		return fp.GetFlightPlanData().GetCapibilities();
	}

	CString FlightPlanDataProvider::GetFlightPlanType()
	{
		return fp.GetFlightPlanData().GetPlanType();
	}

	CString FlightPlanDataProvider::GetLabelData()
	{
		return FlightPlanExtension(fp).GetOpDataText();
	}

	int FlightPlanDataProvider::GetAssignedHeading()
	{
		return fp.GetControllerAssignedData().GetAssignedHeading();
	}

	int FlightPlanDataProvider::GetAssignedSpeed()
	{
		return fp.GetControllerAssignedData().GetAssignedSpeed();
	}

	int FlightPlanDataProvider::GetAssignedMach()
	{
		return fp.GetControllerAssignedData().GetAssignedMach();
	}
	CString FlightPlanDataProvider::GetPilotName()
	{
		return fp.GetPilotName();
	}
}
