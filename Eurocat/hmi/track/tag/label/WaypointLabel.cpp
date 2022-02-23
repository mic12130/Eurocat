#include "base/pch.h"

#include "hmi/track/tag/label/WaypointLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	WaypointLabel::WaypointLabel(IFlightPlanDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> WaypointLabel::GetTagLabelContent()
	{
		CString str;
		auto waypoints = data.GetWaypointsAhead(2);

		if (waypoints.size() == 2)
		{
			return std::make_shared<StringContent>(waypoints[0] + " " + waypoints[1]);
		}

		if (waypoints.size() == 1)
		{
			return std::make_shared<StringContent>(waypoints[0]);
		}

		return std::make_shared<StringContent>("");
	}
}
