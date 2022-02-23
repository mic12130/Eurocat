#include "base/pch.h"

#include "hmi/track/tag/label/IdentLabel.h"

#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/tag/label_content/StringContent.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	IdentLabel::IdentLabel(IFlightPlanDataProvider& fp, IRadarTargetDataProvider& rt, IdentDisplayMode displayMode)
		: fp(fp), rt(rt), displayMode(displayMode)
	{
	}

	std::shared_ptr<ITagLabelContent> IdentLabel::GetTagLabelContent()
	{
		switch (displayMode)
		{
		case IdentDisplayMode::Acid:
			return std::make_shared<StringContent>(fp.GetCallsign(), TrackObjectIdSuffix::kAcidLabel);
		case IdentDisplayMode::Ssr:
			return std::make_shared<StringContent>(rt.GetSsr());
		case IdentDisplayMode::TargetId:
			return std::make_shared<StringContent>(rt.GetTargetId());
		}

		throw std::runtime_error("Unhandled IdentDisplayMode");
	}
}
