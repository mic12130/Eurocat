#pragma once

#include "plugin/ITagItemProvider.h"
#include "hmi/unit/UnitDisplayManager.h"

namespace Eurocat::TagItem
{
	class CflTagItem : public Plugin::ITagItemProvider
	{
	public:
		CflTagItem(Hmi::Unit::UnitDisplayManager& unitDisplayManager);
		void ProcessTagItem(
			EuroScopePlugIn::CFlightPlan flightPlan, 
			EuroScopePlugIn::CRadarTarget radarTarget, 
			int itemCode, char itemString[16], int* colorCode, COLORREF* rgb
		) override;

	private:
		Hmi::Unit::UnitDisplayManager& unitDisplayManager;
	};
}
