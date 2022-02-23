#pragma once

#include "base/pch.h"

#include "common/FlightPlanState.h"

namespace Eurocat::Common
{
	class FlightPlanStateMaker
	{
	public:
		static FlightPlanState Make(int state)
		{
			switch (state)
			{
			case EuroScopePlugIn::FLIGHT_PLAN_STATE_NON_CONCERNED:
			case EuroScopePlugIn::FLIGHT_PLAN_STATE_NOTIFIED:
			case EuroScopePlugIn::FLIGHT_PLAN_STATE_COORDINATED:
			case EuroScopePlugIn::FLIGHT_PLAN_STATE_REDUNDANT:
				return FlightPlanState::Uncontrolled;
			case EuroScopePlugIn::FLIGHT_PLAN_STATE_ASSUMED:
				return FlightPlanState::Controlled;
			case EuroScopePlugIn::FLIGHT_PLAN_STATE_TRANSFER_TO_ME_INITIATED:
				return FlightPlanState::HandedOverFirst;
			case EuroScopePlugIn::FLIGHT_PLAN_STATE_TRANSFER_FROM_ME_INITIATED:
				return FlightPlanState::HandedOver;
			default:
				break;
			}

			return FlightPlanState::Uncontrolled;
		}
	};
}
