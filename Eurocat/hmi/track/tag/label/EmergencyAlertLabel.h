#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/tag/alert/TagAlertData.h"

namespace Eurocat::Hmi::Track
{
	class EmergencyAlertLabel : public ITagLabel
	{
	public:
		EmergencyAlertLabel(TagAlertData& data);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		TagAlertData data;

		const Gdiplus::Color kRed = Gdiplus::Color(255, 50, 50);
	};
}
