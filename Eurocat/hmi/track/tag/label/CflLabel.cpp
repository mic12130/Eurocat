#include "base/pch.h"

#include "hmi/track/tag/label/CflLabel.h"

#include "hmi/track/TrackObjectIdSuffix.h"
#include "hmi/track/tag/label_content/StringContent.h"
#include "common/unit/AltitudeConverter.h"
#include "common/unit/AltitudeFormatter.h"

using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Hmi::Track
{
	CflLabel::CflLabel(IFlightPlanDataProvider& data, UnitDisplayMode unit)
		: data(data), unit(unit)
	{
	}

	std::shared_ptr<ITagLabelContent> CflLabel::GetTagLabelContent()
	{
		auto feets = data.GetCfl();
		bool isNone = feets == std::nullopt;
		AltitudeFormatter formatter(unit);
		CString str;

		if (isNone)
		{
			if (unit == UnitDisplayMode::Imperial)
				str = "   ";
			else if (unit == UnitDisplayMode::Metric)
				str = "    ";
		}
		else if (unit == UnitDisplayMode::Imperial)
		{
			if (feets.value() > 99999 || feets.value() < 0)
			{
				str = "   ";
			}
			else
			{
				str = formatter.StringFromAltitude(feets.value());
			}
		}
		else if (unit == UnitDisplayMode::Metric)
		{
			int meters = AltitudeConverter::FeetToMeter(feets.value()) / 100 * 100;

			if (meters > 99999 || meters < 0 || isNone)
			{
				str = "    ";
			}
			else
			{
				str = formatter.StringFromAltitude(meters);
			}
		}

		if (data.IsCflAcknowledged() == false)
		{
			return std::make_shared<StringContent>(CStringW(str), TrackObjectIdSuffix::kCflLabel, false, Gdiplus::Color(255, 255, 255));
		}

		return std::make_shared<StringContent>(CStringW(str), TrackObjectIdSuffix::kCflLabel);
	}
}
