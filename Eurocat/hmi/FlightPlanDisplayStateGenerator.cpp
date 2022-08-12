#include "base/pch.h"

#include "hmi/FlightPlanDisplayStateGenerator.h"

#include "plugin/extension/FlightPlanExtension.h"

using namespace Eurocat::Common;
using namespace Eurocat::Plugin;

namespace Eurocat::Hmi
{
	auto FlightPlanDisplayStateGenerator::Generate(EuroScopePlugIn::CFlightPlan& fp) -> FlightPlanDisplayState
	{
		auto fpState = FlightPlanExtension(fp).GetCurrentState();
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

	bool FlightPlanDisplayStateGenerator::IsAcceptedReminding(EuroScopePlugIn::CFlightPlan& fp)
	{
		auto fpExtension = FlightPlanExtension(fp);
		auto currentState = fpExtension.GetCurrentState();
		auto lastState = fpExtension.GetLastState();
		auto lastStateUpdateTime = fpExtension.GetLastStateUpdateTime();

		return currentState == FlightPlanState::Uncontrolled &&
			(lastState == FlightPlanState::Controlled || lastState == FlightPlanState::HandedOver) &&
			CTimeSpan(CTime::GetCurrentTime() - lastStateUpdateTime).GetTotalSeconds() <= 15;
	}
}
