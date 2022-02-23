#include "base/pch.h"

#include "hmi/track/tag/label/LabelDataLabel.h"

#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	LabelDataLabel::LabelDataLabel(IFlightPlanDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> LabelDataLabel::GetTagLabelContent()
	{
		CString labelData = data.GetLabelData();

		// If everything is empty, some spaces are still required to make a clickable area
		if (labelData.IsEmpty())
		{
			labelData = "     ";
		}

		return std::make_shared<StringContent>(labelData, TrackObjectIdSuffix::kLabelDataLabel);
	}
}
