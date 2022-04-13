#include "base/pch.h"

#include "hmi/track/FlightPlanDataProvider.h"

#include "helper/CoordinateHelper.h"
#include "common/FlightPlanStateMaker.h"
#include "common/OpData.h"
#include "hmi/FlightPlanDisplayStateGenerator.h"
#include "plugin/extension/CflData.h"

using namespace Eurocat::Hmi;
using namespace Eurocat::Common;
using namespace Eurocat::Plugin::Extension;

namespace Eurocat::Hmi::Track
{
	FlightPlanDataProvider::FlightPlanDataProvider(
		EuroScopePlugIn::CFlightPlan& fp,
		Plugin::Extension::FlightPlanAttribute& fpAttribute)
		: fp(fp), fpAttribute(fpAttribute)
	{
	}

	CString FlightPlanDataProvider::GetCallsign()
	{
		return fp.GetCallsign();
	}

	Hmi::FlightPlanDisplayState FlightPlanDataProvider::GetDisplayState()
	{
		return FlightPlanDisplayStateGenerator::Generate(fp, fpAttribute);
	}

	bool FlightPlanDataProvider::IsAcceptedReminding()
	{
		return FlightPlanDisplayStateGenerator::IsAcceptedReminding(fpAttribute);
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
		return CflData::GetForFlightPlan(fp);
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
		return fpAttribute.lastStateUpdateTime;
	}

	int FlightPlanDataProvider::GetRfl()
	{
		return fp.GetFinalAltitude();
	}

	bool FlightPlanDataProvider::IsCflAcknowledged()
	{
		return fpAttribute.isCflAcknowledged;
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
		return OpData::GetForFlightPlan(fp);
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
