#include "base/pch.h"

#include "tagitem/CflTagItem.h"

#include "common/unit/AltitudeConverter.h"
#include "common/unit/AltitudeFormatter.h"
#include "plugin/extension/FlightPlanAttributeContainer.h"
#include "tagitem/TagItemColor.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Plugin::Extension;
using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::TagItem
{
	CflTagItem::CflTagItem(Hmi::Unit::UnitDisplayManager& unitDisplayManager) : unitDisplayManager(unitDisplayManager)
	{
	}

	void CflTagItem::ProcessTagItem(
		EuroScopePlugIn::CFlightPlan flightPlan,
		EuroScopePlugIn::CRadarTarget radarTarget,
		int itemCode, char itemString[16], int* colorCode, COLORREF* rgb)
	{
		auto fpAttribute = FlightPlanAttributeContainer::Shared().AttributeForFlightPlan(flightPlan);
		int level = flightPlan.GetControllerAssignedData().GetClearedAltitude();
		UnitDisplayMode unit = unitDisplayManager.GetUnitForFlightPlan(flightPlan.GetCallsign());
		AltitudeFormatter formatter(unit);

		if (unit == UnitDisplayMode::Metric)
		{
			level = AltitudeConverter::FeetToMeter(level);
		}

		CString str = formatter.StringFromAltitude(level);
		strcpy_s(itemString, 16, str);
		*colorCode = EuroScopePlugIn::TAG_COLOR_RGB_DEFINED;
		*rgb = TagItemColor::GetIdenticalColor(flightPlan, fpAttribute);
	}
}
