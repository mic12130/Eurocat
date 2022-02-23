#pragma once

#include "hmi/track/tag/label/ITagLabel.h"

namespace Eurocat::Hmi::Track
{
	class SpaceLabel : public ITagLabel
	{
	public:
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;
	};
}
