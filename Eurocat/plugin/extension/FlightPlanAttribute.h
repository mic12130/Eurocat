#pragma once

#include "common/FlightPlanState.h"

namespace Eurocat::Plugin
{
	// Flight plan attributes that will be stored locally and will not interact with the ES API
	struct FlightPlanAttribute
	{
		bool isCflAcknowledged = false;
		Common::FlightPlanState currentState;
		Common::FlightPlanState lastState;
		CTime lastStateUpdateTime;
	};
}
