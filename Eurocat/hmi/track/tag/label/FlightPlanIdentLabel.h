#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/option/IdentDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class FlightPlanIdentLabel : public ITagLabel
	{

	public:
		FlightPlanIdentLabel(IFlightPlanDataProvider& fp, IdentDisplayMode displayMode);

		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IFlightPlanDataProvider& fp;
		IdentDisplayMode displayMode;
	};
}
