#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IFlightPlanDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class AircraftTypeLabel : public ITagLabel
	{
	public:
		AircraftTypeLabel(IFlightPlanDataProvider& data);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IFlightPlanDataProvider& data;
	};
}
