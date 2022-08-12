#include "base/pch.h"

#include "tagitem/AcidTagItem.h"

#include "tagitem/TagItemColor.h"

namespace Eurocat::TagItem
{
	void AcidTagItem::ProcessTagItem(
		EuroScopePlugIn::CFlightPlan flightPlan,
		EuroScopePlugIn::CRadarTarget radarTarget,
		int itemCode, char itemString[16], int* colorCode, COLORREF* rgb)
	{
		if (!flightPlan.IsValid())
		{
			strcpy_s(itemString, 16, "--------");
		}

		strcpy_s(itemString, 16, flightPlan.GetCallsign());
		*colorCode = EuroScopePlugIn::TAG_COLOR_RGB_DEFINED;
		*rgb = TagItemColor::GetIdenticalColor(flightPlan);
	}
}
