#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IFlightPlanDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class WtcLabel : public ITagLabel
	{
	public:
		WtcLabel(IFlightPlanDataProvider& data);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IFlightPlanDataProvider& data;
	};
}
