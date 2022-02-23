#include "base/pch.h"

#include "hmi/track/tag/label/DestLabel.h"

#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	DestLabel::DestLabel(IFlightPlanDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> DestLabel::GetTagLabelContent()
	{
		return std::make_shared<StringContent>(data.GetDestination(), TrackObjectIdSuffix::kDestLabel);
	}
}
