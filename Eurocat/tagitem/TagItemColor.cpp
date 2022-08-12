#include "base/pch.h"

#include "tagitem/TagItemColor.h"
#include "hmi/FlightPlanDisplayStateGenerator.h"
#include "plugin/extension/FlightPlanExtension.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Common;
using namespace Eurocat::Hmi;

namespace Eurocat::TagItem
{
	COLORREF TagItemColor::GetIdenticalColor(EuroScopePlugIn::CFlightPlan& fp)
	{
		auto displayState = FlightPlanDisplayStateGenerator::Generate(fp);
		COLORREF result = RGB(0, 0, 0);

		if (IsEmergency(fp))
		{
			result = RGB(209, 46, 46);
		}
		else if (displayState == FlightPlanDisplayState::Announced)
		{
			result = RGB(0, 0, 180);
		}
		else if (displayState == FlightPlanDisplayState::NotConcerned)
		{
			result = RGB(0, 0, 0);
		}
		else if (displayState == FlightPlanDisplayState::HandOverIn || displayState == FlightPlanDisplayState::HandOverOut)
		{
			result = RGB(255, 205, 105);
		}
		else if (displayState == FlightPlanDisplayState::Jurisdiction)
		{
			result = RGB(170, 255, 170);
		}

		return result;
	}

	bool TagItemColor::IsEmergency(EuroScopePlugIn::CFlightPlan& fp)
	{
		auto rt = fp.GetCorrelatedRadarTarget();

		if (rt.IsValid() == false)
		{
			return false;
		}

		CString squawk = rt.GetPosition().GetSquawk();
		return squawk == "7500" || squawk == "7600" || squawk == "7700";
	}
}
