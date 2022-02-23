#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IRadarTargetDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class AccIndicatorLabel : public ITagLabel
	{
	public:
		AccIndicatorLabel(IRadarTargetDataProvider& data);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IRadarTargetDataProvider& data;
	};
}
