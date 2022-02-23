#pragma once

#include "base/pch.h"

#include "hmi/track/option/IdentDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	struct OptionData
	{
		bool showFlightPlanTracks = true;
		bool enableSharedLabel = false;
		bool enableExtendedLabel = false;
		int altitudeFilterHigh = -1;
		int altitudeFilterLow = -1;
		IdentDisplayMode identDisplayMode = IdentDisplayMode::Acid;
		bool hidePsrSymbol = false;
		bool enableVelocityVectorDisplay = false;
		int velocityVectorMinutes = 1;
		bool enableShortRouteProbeDisplay = false;
		// SrpConfig shortRouteProbeConfig = 0;
		bool enableHistoryDotsDisplay = false;
		int historyDotsCount = 5;
	};
}
