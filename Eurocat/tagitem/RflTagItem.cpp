#include "base/pch.h"

#include "tagitem/RflTagItem.h"

#include "common/unit/AltitudeConverter.h"
#include "common/unit/AltitudeFormatter.h"
#include "common/unit/RflConverter.h"
#include "tagitem/TagItemColor.h"

using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::TagItem
{
	RflTagItem::RflTagItem(Hmi::Unit::UnitDisplayManager& unitDisplayManager) : unitDisplayManager(unitDisplayManager)
	{
	}

	void RflTagItem::ProcessTagItem(
		EuroScopePlugIn::CFlightPlan flightPlan,
		EuroScopePlugIn::CRadarTarget radarTarget,
		int itemCode, char itemString[16], int* colorCode, COLORREF* rgb)
	{
		RflModel rflModel = RflConverter::GetRflFromEsFormat(flightPlan.GetFinalAltitude());
		UnitDisplayMode unit = unitDisplayManager.GetUnitForFlightPlan(flightPlan.GetCallsign());
		AltitudeFormatter formatter(unit);
		CString str;

		// If RFL's unit is equal to the UDM, print it out directly, otherwise make a conversion before formatting
		if (rflModel.isMeter == (unit == UnitDisplayMode::Metric))
		{
			str = formatter.StringFromAltitude(rflModel.value);
		}
		else
		{
			int converted = rflModel.isMeter ? AltitudeConverter::MeterToFeet(rflModel.value) : AltitudeConverter::FeetToMeter(rflModel.value);
			str = formatter.StringFromAltitude(converted);
		}

		strcpy_s(itemString, 16, str);
		*colorCode = EuroScopePlugIn::TAG_COLOR_RGB_DEFINED;
		*rgb = TagItemColor::kRegularColor;
	}
}
