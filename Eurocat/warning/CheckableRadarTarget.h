#pragma once

#include "base/pch.h"

namespace Eurocat::Warning
{
	struct CheckableRadarTarget
	{
		CString targetId;
		CString squawk;
		int pressureAltitude;
		int flightLevel;
		int heading;
		int groundSpeed;

		CheckableRadarTarget(
			CString targetId, CString squawk,
			int pressureAltitude, int flightLevel,
			int heading, int groundSpeed)
			: targetId(targetId), squawk(squawk),
			pressureAltitude(pressureAltitude), flightLevel(flightLevel),
			heading(heading), groundSpeed(groundSpeed)
		{
		}

		CheckableRadarTarget(EuroScopePlugIn::CRadarTarget& rt)
			: CheckableRadarTarget(rt.GetCallsign(), "", 0, 0, 0, 0)
		{
			auto pos = rt.GetPosition();
			squawk = pos.GetSquawk();
			pressureAltitude = pos.GetPressureAltitude();
			flightLevel = pos.GetFlightLevel();
			heading = pos.GetReportedHeading();
			groundSpeed = pos.GetReportedGS();
		}
	};
}