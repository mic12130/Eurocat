#pragma once

namespace Eurocat::TagItem
{
	class TagItemColor
	{
	public:
		static COLORREF GetIdenticalColor(EuroScopePlugIn::CFlightPlan& fp);

		inline static const COLORREF kRegularColor = RGB(220, 220, 220);

	private:
		static bool IsAnnounced(EuroScopePlugIn::CFlightPlan& fp);
		static bool IsEmergency(EuroScopePlugIn::CFlightPlan& fp);
	};
}
