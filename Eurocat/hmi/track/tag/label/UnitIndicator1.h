#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	// Single character indicating that the RFL unit (Metric or Imperial) of the flight plan
	// is different from the Unit Display Mode.
	class UnitIndicator1 : public ITagLabel
	{
	public:
		UnitIndicator1(IFlightPlanDataProvider& data, Hmi::Unit::UnitDisplayMode unit);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IFlightPlanDataProvider& data;
		Hmi::Unit::UnitDisplayMode unit;
	};
}
