#include "base/pch.h"

#include "tagitem/OpDataTagItem.h"

#include "tagitem/TagItemColor.h"
#include "plugin/extension/FlightPlanExtension.h"

using namespace Eurocat::Plugin;

namespace Eurocat::TagItem
{
	void OpDataTagItem::ProcessTagItem(
		EuroScopePlugIn::CFlightPlan flightPlan,
		EuroScopePlugIn::CRadarTarget radarTarget,
		int itemCode, char itemString[16], int* colorCode, COLORREF* rgb)
	{
		CString str = FlightPlanExtension(flightPlan).GetOpDataText();
		strcpy_s(itemString, 16, str);
		*colorCode = EuroScopePlugIn::TAG_COLOR_RGB_DEFINED;
		*rgb = TagItemColor::kRegularColor;
	}
}
