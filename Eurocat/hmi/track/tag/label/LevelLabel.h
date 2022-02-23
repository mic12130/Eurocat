#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class LevelLabel : public ITagLabel
	{
	public:
		LevelLabel(IRadarTargetDataProvider& data, Hmi::Unit::UnitDisplayMode unit, bool aboveTa);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IRadarTargetDataProvider& data;
		Hmi::Unit::UnitDisplayMode unit;
		bool aboveTa;
	};
}
