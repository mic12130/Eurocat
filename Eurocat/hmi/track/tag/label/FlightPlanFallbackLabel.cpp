#include "base/pch.h"

#include "hmi/track/tag/label/FlightPlanFallbackLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Hmi::Track
{
	LevelFallbackLabel::LevelFallbackLabel(UnitDisplayMode unit) : unit(unit)
	{
	}

	std::shared_ptr<ITagLabelContent> LevelFallbackLabel::GetTagLabelContent()
	{
		if (unit == UnitDisplayMode::Imperial)
		{
			return std::make_shared<StringContent>("000");
		}

		if (unit == UnitDisplayMode::Metric)
		{
			return std::make_shared<StringContent>("0000");
		}

		throw std::runtime_error("Unhandled UnitDisplayMode");
	}

	GroundSpeedFallbackLabel::GroundSpeedFallbackLabel(UnitDisplayMode unit) : unit(unit)
	{
	}

	std::shared_ptr<ITagLabelContent> GroundSpeedFallbackLabel::GetTagLabelContent()
	{
		if (unit == UnitDisplayMode::Imperial)
		{
			return std::make_shared<StringContent>("00");
		}

		if (unit == UnitDisplayMode::Metric)
		{
			return std::make_shared<StringContent>("000");
		}

		throw std::runtime_error("Unhandled UnitDisplayMode");
	}
}
