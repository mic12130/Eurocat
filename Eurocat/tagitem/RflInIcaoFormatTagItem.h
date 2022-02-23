#pragma once

#include "plugin/ITagItemProvider.h"

namespace Eurocat::TagItem
{
	class RflInIcaoFormatTagItem : public Plugin::ITagItemProvider
	{
	public:
		void ProcessTagItem(
			EuroScopePlugIn::CFlightPlan flightPlan,
			EuroScopePlugIn::CRadarTarget radarTarget,
			int itemCode, char itemString[16], int* colorCode, COLORREF* rgb
		) override;
	};
}
