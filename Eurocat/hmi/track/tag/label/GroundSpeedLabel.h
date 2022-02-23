#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class GroundSpeedLabel : public ITagLabel
	{
	public:
		GroundSpeedLabel(IRadarTargetDataProvider& data, Hmi::Unit::UnitDisplayMode unit);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		IRadarTargetDataProvider& data;
		Hmi::Unit::UnitDisplayMode unit;

		const int kMaxKnots = 994;
		const int kMaxKph = 1994;
	};
}
