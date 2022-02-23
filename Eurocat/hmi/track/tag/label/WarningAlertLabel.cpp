#include "base/pch.h"

#include "hmi/track/tag/label/WarningAlertLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	WarningAlertLabel::WarningAlertLabel(TagAlertData& data) : data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> WarningAlertLabel::GetTagLabelContent()
	{
		if (data.warningInfo.has_value())
		{
			auto info = data.warningInfo.value();

			if (info.style == WarningInfo::Style::Style1)
			{
				return std::make_shared<StringContent>(CStringW(info.code), "", false, kBlack, kYellow);
			}
			if (info.style == WarningInfo::Style::Style2)
			{
				return std::make_shared<StringContent>(CStringW(info.code), "", false, kRedText, kRed);
			}
		}

		return std::make_shared<StringContent>("");
	}
}
