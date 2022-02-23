#pragma once

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class LevelFallbackLabel : public ITagLabel
	{
	public:
		LevelFallbackLabel(Hmi::Unit::UnitDisplayMode unit);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		Hmi::Unit::UnitDisplayMode unit;
	};

	class GroundSpeedFallbackLabel : public ITagLabel
	{
	public:
		GroundSpeedFallbackLabel(Hmi::Unit::UnitDisplayMode unit);
		std::shared_ptr<ITagLabelContent> GetTagLabelContent() override;

	private:
		Hmi::Unit::UnitDisplayMode unit;
	};
}
