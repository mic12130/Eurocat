#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/tag/alert/TagAlertData.h"

namespace Eurocat::Hmi::Track
{
	class WarningAlertLabel : public ITagLabel
	{
	public:
		WarningAlertLabel(TagAlertData& data);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		TagAlertData data;

		const Gdiplus::Color kRed = Gdiplus::Color(255, 50, 50);
		const Gdiplus::Color kYellow = Gdiplus::Color(255, 255, 0);
		const Gdiplus::Color kBlack = Gdiplus::Color(0, 0, 0);
		const Gdiplus::Color kRedText = Gdiplus::Color(130, 30, 30);
	};
}
