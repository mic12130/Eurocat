#pragma once

#include "plugin/extension/FlightPlanAttribute.h"

namespace Eurocat::TagItem
{
	class TagItemColor
	{
	public:
		static COLORREF GetIdenticalColor(EuroScopePlugIn::CFlightPlan& fp, Plugin::Extension::FlightPlanAttribute& fpAttribute);

		inline static const COLORREF kRegularColor = RGB(220, 220, 220);

	private:
		static bool IsAnnounced(EuroScopePlugIn::CFlightPlan& fp, Plugin::Extension::FlightPlanAttribute& fpAttribute);
		static bool IsEmergency(EuroScopePlugIn::CFlightPlan& fp);
	};
}
