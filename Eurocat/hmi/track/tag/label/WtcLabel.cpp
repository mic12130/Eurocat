#include "base/pch.h"

#include "hmi/track/tag/label/WtcLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	WtcLabel::WtcLabel(IFlightPlanDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> WtcLabel::GetTagLabelContent()
	{
		return std::make_shared<StringContent>(CString(data.GetWtc()));
	}
}
