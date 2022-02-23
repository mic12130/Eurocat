#pragma once

#include "hmi/track/tag/label/ITagLabel.h"

namespace Eurocat::Hmi::Track
{
	// Not implemented
	//
	// Single character indicating that the Position Unit Setting (Metric or Imperial)
	// is different from the Unit Display Mode
	class UnitIndicator2 : public ITagLabel
	{
	public:
		UnitIndicator2();
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;
	};
}
