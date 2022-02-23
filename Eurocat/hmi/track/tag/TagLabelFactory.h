#pragma once

#include "hmi/track/tag/TagLabelCollection.h"
#include "hmi/track/tag/alert/TagAlertData.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/option/OptionData.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class TagLabelFactory
	{
	public:
		TagLabelCollection GetLimitedTagLabels(
			IRadarTargetDataProvider& rt,
			TagAlertData& alertData,
			Hmi::Unit::UnitDisplayMode unit,
			IdentDisplayMode identDisplayMode,
			bool aboveTransAltitude
		);
		TagLabelCollection GetTagLabelsForCoupledTrack(
			IRadarTargetDataProvider& rt,
			IFlightPlanDataProvider& fp,
			TagAlertData& alertData,
			Hmi::Unit::UnitDisplayMode unit,
			IdentDisplayMode identDisplayMode,
			bool aboveTransAltitude,
			bool extended,
			bool shared
		);
		TagLabelCollection GetTagLabelsForFlightPlanTrack(
			IFlightPlanDataProvider& fp,
			TagAlertData& alertData,
			Hmi::Unit::UnitDisplayMode unit,
			IdentDisplayMode identDisplayMode,
			bool extended,
			bool shared
		);
	};
}
