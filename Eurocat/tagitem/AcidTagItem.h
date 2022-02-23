#pragma once

#include "plugin/ITagItemProvider.h"

namespace Eurocat::TagItem
{
	class AcidTagItem : public Plugin::ITagItemProvider
	{
	public:
		void ProcessTagItem(
			EuroScopePlugIn::CFlightPlan flightPlan, 
			EuroScopePlugIn::CRadarTarget radarTarget, 
			int itemCode, char itemString[16], int* colorCode, COLORREF* rgb
		) override;
	};
}
