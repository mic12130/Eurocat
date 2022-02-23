#pragma once

#include "base/pch.h"

#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/IFlightPlanDataProvider.h"

namespace Eurocat::Hmi::Track
{
	namespace TrackColor
	{
		const Gdiplus::Color kBlue(0, 0, 255);
		const Gdiplus::Color kBlack(0, 0, 0);
		const Gdiplus::Color kWhite(255, 255, 255);
		const Gdiplus::Color kGreen(0, 255, 0);
		const Gdiplus::Color kGreenLt(200, 255, 200);
		const Gdiplus::Color kOrange(255, 205, 105);
		const Gdiplus::Color kRed(209, 46, 46);
		const Gdiplus::Color kYellow(225, 225, 40);
		const Gdiplus::Color kCyan(0, 255, 255);

		inline Gdiplus::Color GetGroundTrackColor()
		{
			return kBlack;
		}

		inline Gdiplus::Color GetPsrTrackColor()
		{
			return kBlack;
		}

		inline Gdiplus::Color GetUncoupledTrackColor(bool isIql)
		{
			return isIql ? kWhite : kBlack;
		}

		inline Gdiplus::Color GetTrackColor(IFlightPlanDataProvider& fp, bool isIql)
		{
			auto state = fp.GetDisplayState();

			// Accepted reminding and IQL will override the display-state-based colors
			if (fp.IsAcceptedReminding())
			{
				return kWhite;
			}

			if (isIql)
			{
				if (state == Hmi::FlightPlanDisplayState::NotConcerned || state == Hmi::FlightPlanDisplayState::Announced)
				{
					return kWhite;
				}
				if (state == Hmi::FlightPlanDisplayState::Jurisdiction)
				{
					return kGreen;
				}
			}

			// Uses display-state-based colors by default
			if (state == Hmi::FlightPlanDisplayState::NotConcerned)
			{
				return kBlack;
			}
			if (state == Hmi::FlightPlanDisplayState::Announced)
			{
				return kBlue;
			}
			if (state == Hmi::FlightPlanDisplayState::HandOverIn || state == Hmi::FlightPlanDisplayState::HandOverOut)
			{
				return kOrange;
			}
			if (state == Hmi::FlightPlanDisplayState::Jurisdiction)
			{
				return kGreenLt;
			}

			throw std::runtime_error("Unhandled flight plan display state");
		}
	}
}
