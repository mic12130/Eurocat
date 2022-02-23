#include "base/pch.h"

#include "hmi/track/tag/label/UncoupledIdentLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	UncoupledIdentLabel::UncoupledIdentLabel(IRadarTargetDataProvider& rt, IdentDisplayMode displayMode)
		: rt(rt), displayMode(displayMode)
	{
		if (displayMode == IdentDisplayMode::Acid)
		{
			throw std::invalid_argument("ACID display is not available without a FP given");
		}
	}

	std::shared_ptr<ITagLabelContent> UncoupledIdentLabel::GetTagLabelContent()
	{
		if (displayMode == IdentDisplayMode::Ssr)
		{
			return std::make_shared<StringContent>(rt.GetSsr());
		}

		if (displayMode == IdentDisplayMode::TargetId)
		{
			return std::make_shared<StringContent>(rt.GetTargetId());
		}

		throw std::runtime_error("Unhandled IdentDisplayMode");
	}
}
