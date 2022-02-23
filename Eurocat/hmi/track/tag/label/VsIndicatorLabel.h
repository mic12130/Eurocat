#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IRadarTargetDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class VsIndicatorLabel : public ITagLabel
	{
	public:
		VsIndicatorLabel(IRadarTargetDataProvider& data);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IRadarTargetDataProvider& data;
	};
}
