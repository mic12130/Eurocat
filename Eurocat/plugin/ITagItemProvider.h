#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin
{
	class ITagItemProvider
	{
	public:
		virtual ~ITagItemProvider() = default;
		virtual void ProcessTagItem(
			EuroScopePlugIn::CFlightPlan flightPlan,
			EuroScopePlugIn::CRadarTarget radarTarget,
			int itemCode,
			char itemString[16],
			int* colorCode,
			COLORREF* rgb) = 0;
	};
}
