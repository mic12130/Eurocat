#pragma once

#include "base/pch.h"

#include "hmi/track/profile/TrackProfile.h"
#include "hmi/track/option/OptionData.h"
#include "hmi/track/IFlightPlanDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class ExtendedLabelCalc
	{
	public:
		// Checks if extended label should be rendered for a coupled or flight plan track
		static bool RendersExtendedLabel(const OptionData& option, IFlightPlanDataProvider& fp, const TrackProfile& profile)
		{
			// If user has manually set an extended behaviour, then it will have the highest priority
			// and override the global one set in the OptionData
			if (profile.userSetExtended.has_value())
			{
				return profile.userSetExtended.value();
			}

			// If user has not manually set an extended behaviour, then we will follow the default rule:
			// - If option.enableExtendedLabel is false, normal label should be displayed
			// - If option.enableExtendedLabel is true, only jurisdiction, handover in/out, announced tracks
			// should get extended labels, and the rest should get normal labels
			if (option.enableExtendedLabel)
			{
				auto state = fp.GetDisplayState();

				if (state == Hmi::FlightPlanDisplayState::Jurisdiction ||
					state == Hmi::FlightPlanDisplayState::HandOverIn ||
					state == Hmi::FlightPlanDisplayState::HandOverOut ||
					state == Hmi::FlightPlanDisplayState::Announced)
				{
					return true;
				}
			}

			return false;
		}
	};
}
