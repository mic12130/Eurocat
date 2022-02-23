#include "base/pch.h"

#include "hmi/track/tag/label/EmergencyAlertLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	EmergencyAlertLabel::EmergencyAlertLabel(TagAlertData& data) : data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> EmergencyAlertLabel::GetTagLabelContent()
	{
		if (data.emergencyInfo.has_value())
		{
			auto info = data.emergencyInfo.value();

			return std::make_shared<StringContent>(CStringW(info.code), "", false, kRed);
		}

		return std::make_shared<StringContent>("");
	}
}
