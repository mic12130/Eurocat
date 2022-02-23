#pragma once

#include "common/FlightPlanState.h"

namespace Eurocat::Plugin::Extension
{
	struct FlightPlanAttribute
	{
		bool isCflAcknowledged = false;
		Common::FlightPlanState currentState;
		Common::FlightPlanState lastState;
		CTime lastStateUpdateTime;
	};
}
