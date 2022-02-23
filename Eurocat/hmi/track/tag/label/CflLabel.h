#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class CflLabel : public ITagLabel
	{
	public:
		CflLabel(IFlightPlanDataProvider& data, Hmi::Unit::UnitDisplayMode unit);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IFlightPlanDataProvider& data;
		Hmi::Unit::UnitDisplayMode unit;
	};
}
