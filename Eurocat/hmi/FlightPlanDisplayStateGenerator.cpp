#include "base/pch.h"

#include "hmi/FlightPlanDisplayStateGenerator.h"

using namespace Eurocat::Common;

namespace Eurocat::Hmi
{
	auto FlightPlanDisplayStateGenerator::Generate(const EuroScopePlugIn::CFlightPlan& fp, const Plugin::Extension::FlightPlanAttribute& fpAttribute) -> FlightPlanDisplayState
	{
		auto fpState = fpAttribute.currentState;
		FlightPlanDisplayState result;

		if (fpState == FlightPlanState::Uncontrolled)
		{
			if (fp.GetSectorEntryMinutes() <= 5 && fp.GetSectorEntryMinutes() > -1)
			{
				result = FlightPlanDisplayState::Announced;
			}
			else
			{
				result = FlightPlanDisplayState::NotConcerned;
			}
		}
		else if (fpState == FlightPlanState::HandedOverFirst)
		{
			result = FlightPlanDisplayState::HandOverIn;
		}
		else if (fpState == FlightPlanState::HandedOver)
		{
			result = FlightPlanDisplayState::HandOverOut;
		}
		else if (fpState == FlightPlanState::Controlled)
		{
			result = FlightPlanDisplayState::Jurisdiction;
		}
		else
		{
			throw std::runtime_error("Unhandled flight plan state");
		}

		return result;
	}

	bool FlightPlanDisplayStateGenerator::IsAcceptedReminding(const Plugin::Extension::FlightPlanAttribute& fpAttribute)
	{
		return fpAttribute.currentState == FlightPlanState::Uncontrolled &&
			(fpAttribute.lastState == FlightPlanState::Controlled || fpAttribute.lastState == FlightPlanState::HandedOver) &&
			CTimeSpan(CTime::GetCurrentTime() - fpAttribute.lastStateUpdateTime).GetTotalSeconds() <= 15;
	}
}
