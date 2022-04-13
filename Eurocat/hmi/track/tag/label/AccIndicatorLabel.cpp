#include "base/pch.h"

#include "hmi/track/tag/label/AccIndicatorLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	AccIndicatorLabel::AccIndicatorLabel(IRadarTargetDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> AccIndicatorLabel::GetTagLabelContent()
	{
		int gs = data.GetGroundSpeed();
		auto previousGs = data.GetHistoricalGroundSpeeds(1);

		// Returns if historical GS is not accessible
		if (previousGs.empty())
		{
			return std::make_shared<StringContent>(" ");
		}

		if (gs > previousGs[0])
		{
			return std::make_shared<StringContent>("A");
		}

		if (gs < previousGs[0])
		{
			return std::make_shared<StringContent>("L");
		}

		return std::make_shared<StringContent>(" ");
	}
}
