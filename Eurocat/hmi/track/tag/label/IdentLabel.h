#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/option/IdentDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class IdentLabel : public ITagLabel
	{

	public:
		IdentLabel(
			IFlightPlanDataProvider& fp,
			IRadarTargetDataProvider& rt,
			IdentDisplayMode displayMode
		);

		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IFlightPlanDataProvider& fp;
		IRadarTargetDataProvider& rt;
		IdentDisplayMode displayMode;
	};
}
