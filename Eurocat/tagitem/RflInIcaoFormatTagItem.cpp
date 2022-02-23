#include "base/pch.h"

#include "tagitem/RflInIcaoFormatTagItem.h"

#include "common/unit/RflConverter.h"

using namespace Eurocat::Common::Unit;

namespace Eurocat::TagItem
{
	void RflInIcaoFormatTagItem::ProcessTagItem(
		EuroScopePlugIn::CFlightPlan flightPlan,
		EuroScopePlugIn::CRadarTarget radarTarget,
		int itemCode, char itemString[16], int* colorCode, COLORREF* rgb)
	{
		RflModel rflModel = RflConverter::GetRflFromEsFormat(flightPlan.GetFinalAltitude());
		CString str;

		if (rflModel.isMeter)
		{
			str.Format("S%04d", rflModel.value / 10);
		}
		else
		{
			str.Format("F%03d", rflModel.value / 100);
		}

		strcpy_s(itemString, 16, str);
	}
}
