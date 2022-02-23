#include "base/pch.h"

#include "hmi/track/tag/label/GroundSpeedLabel.h"

#include "common/unit/SpeedConverter.h"
#include "common/unit/SpeedFormatter.h"
#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/tag/label_content/StringContent.h"

using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Hmi::Track
{
	GroundSpeedLabel::GroundSpeedLabel(IRadarTargetDataProvider& data, UnitDisplayMode unit)
		: data(data), unit(unit)
	{
	}

	std::shared_ptr<ITagLabelContent> GroundSpeedLabel::GetTagLabelContent()
	{
		SpeedFormatter formatter(unit);
		CString str;
		int knots = data.GetGroundSpeed();

		if (unit == UnitDisplayMode::Imperial)
		{
			if (knots > kMaxKnots)
			{
				str = "++";
			}
			else
			{
				str = formatter.StringFromSpeed(knots);
			}
		}
		else if (unit == UnitDisplayMode::Metric)
		{
			int kph = SpeedConverter::KnotToKph(knots);

			if (kph > kMaxKph)
			{
				str = "+++";
			}
			else
			{
				str = formatter.StringFromSpeed(kph);
			}
		}

		return std::make_shared<StringContent>(str, TrackObjectIdSuffix::kGroundSpeedLabel);
	}
}
