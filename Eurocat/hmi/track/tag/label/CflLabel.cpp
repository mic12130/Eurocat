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
		int feets = data.GetCfl();
		bool isRevValue = (feets == 1 || feets == 2); // Treats reversed values as invalid
		AltitudeFormatter formatter(unit);
		CString str;

		if (unit == UnitDisplayMode::Imperial)
		{
			if (feets > 99999 || feets < 0 || isRevValue)
			{
				str = "   ";
			}
			else
			{
				str = formatter.StringFromAltitude(feets);
			}
		}
		else if (unit == UnitDisplayMode::Metric)
		{
			int meters = AltitudeConverter::FeetToMeter(feets);

			if (meters > 99999 || meters < 0 || isRevValue)
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
