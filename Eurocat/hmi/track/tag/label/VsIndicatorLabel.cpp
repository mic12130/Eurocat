#include "base/pch.h"

#include "hmi/track/tag/label/VsIndicatorLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	VsIndicatorLabel::VsIndicatorLabel(IRadarTargetDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> VsIndicatorLabel::GetTagLabelContent()
	{
		int vs = data.GetVerticalSpeed();

		if (vs > 200)
		{
			return std::make_shared<StringContent>(L"\u2227");
		}

		if (vs < -200)
		{
			return std::make_shared<StringContent>(L"\u2228");
		}

		return std::make_shared<StringContent>(">");
	}
}
