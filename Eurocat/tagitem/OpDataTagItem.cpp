#include "base/pch.h"

#include "tagitem/OpDataTagItem.h"

#include "common/OpData.h"
#include "tagitem/TagItemColor.h"

using namespace Eurocat::Common;

namespace Eurocat::TagItem
{
	void OpDataTagItem::ProcessTagItem(
		EuroScopePlugIn::CFlightPlan flightPlan,
		EuroScopePlugIn::CRadarTarget radarTarget,
		int itemCode, char itemString[16], int* colorCode, COLORREF* rgb)
	{
		CString str = OpData::GetForFlightPlan(flightPlan);
		strcpy_s(itemString, 16, str);
		*colorCode = EuroScopePlugIn::TAG_COLOR_RGB_DEFINED;
		*rgb = TagItemColor::kRegularColor;
	}
}
