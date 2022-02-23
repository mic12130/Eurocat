#include "base/pch.h"

#include "hmi/track/tag/label/RunwayLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"
#include "hmi/track/TrackObjectIdSuffix.h"

namespace Eurocat::Hmi::Track
{
	RunwayLabel::RunwayLabel(IFlightPlanDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> RunwayLabel::GetTagLabelContent()
	{
		CString rwy = data.GetArrivalRunway();

		if (rwy == "")
		{
			return std::make_shared<StringContent>(" ", TrackObjectIdSuffix::kRunwayLabel);
		}

		return std::make_shared<StringContent>(rwy, TrackObjectIdSuffix::kRunwayLabel);
	}
}
