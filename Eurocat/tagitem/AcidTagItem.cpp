#include "base/pch.h"

#include "tagitem/AcidTagItem.h"

#include "plugin/PluginEnvironment.h"
#include "tagitem/TagItemColor.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Common;

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

		auto fpAttribute = PluginEnvironment::Shared().AttributeForFlightPlan(flightPlan);

		strcpy_s(itemString, 16, flightPlan.GetCallsign());
		*colorCode = EuroScopePlugIn::TAG_COLOR_RGB_DEFINED;
		*rgb = TagItemColor::GetIdenticalColor(flightPlan, fpAttribute);
	}
}
