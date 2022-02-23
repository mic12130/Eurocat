#include "base/pch.h"

#include "hmi/track/tag/label/FlightPlanIdentLabel.h"

#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/tag/label_content/StringContent.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	FlightPlanIdentLabel::FlightPlanIdentLabel(IFlightPlanDataProvider& fp, IdentDisplayMode displayMode)
		: fp(fp), displayMode(displayMode)
	{
		if (displayMode == IdentDisplayMode::Ssr || displayMode == IdentDisplayMode::TargetId)
		{
			throw std::invalid_argument("SSR or Target ID display is not available without a RT given");
		}
	}

	std::shared_ptr<ITagLabelContent> FlightPlanIdentLabel::GetTagLabelContent()
	{
		return std::make_shared<StringContent>(fp.GetCallsign(), TrackObjectIdSuffix::kAcidLabel);
	}
}
