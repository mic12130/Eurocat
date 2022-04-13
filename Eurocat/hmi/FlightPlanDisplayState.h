#pragma once

namespace Eurocat::Hmi
{
	enum class FlightPlanDisplayState
	{
		// Sorted by priority
		NotConcerned,
		Announced,
		Jurisdiction,
		HandOverIn,
		HandOverOut,
	};
}
