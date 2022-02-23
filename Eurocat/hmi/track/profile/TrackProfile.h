#pragma once

#include "base/pch.h"

namespace Eurocat::Hmi::Track
{
	struct TrackProfile
	{
		// Only contains track types that would have a profile
		enum class TrackType
		{
			Uncoupled,
			Coupled,
			FlightPlan
		};

		CString id = "";
		TrackType trackType = TrackType::Uncoupled;
		std::optional<CString> flightPlanId;
		std::optional<CString> radarTargetId;
		int tagOffsetX = 28;
		int tagOffsetY = -28;
		std::optional<bool> userSetExtended;
		std::optional<bool> userSetVel;
		bool isTagRepositioning = false;
		bool isIql = false;
	};
}
