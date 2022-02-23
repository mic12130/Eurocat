#pragma once

#include "plugin/ITagItemProvider.h"

namespace Eurocat::TagItem
{
	class OpDataTagItem : public Plugin::ITagItemProvider
	{
	public:
		void ProcessTagItem(
			EuroScopePlugIn::CFlightPlan flightPlan, 
			EuroScopePlugIn::CRadarTarget radarTarget, 
			int itemCode, char itemString[16], int* colorCode, COLORREF* rgb
		) override;
	};
}
