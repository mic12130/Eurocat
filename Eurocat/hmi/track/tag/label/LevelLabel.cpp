#include "base/pch.h"

#include "hmi/track/tag/label/LevelLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"
#include "common/unit/AltitudeConverter.h"
#include "common/unit/AltitudeFormatter.h"

using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Hmi::Track
{
	LevelLabel::LevelLabel(IRadarTargetDataProvider& data, UnitDisplayMode unit, bool aboveTa)
		: data(data), unit(unit), aboveTa(aboveTa)
	{
	}

	std::shared_ptr<ITagLabelContent> LevelLabel::GetTagLabelContent()
	{
		CString str;
		int feets;
		bool hasUnderline = false;

		// If level is higher than the TA, then an underline will be added
		if (aboveTa)
		{
			feets = data.GetFlightLevel();
		}
		else
		{
			feets = data.GetPressureAltitude();
			hasUnderline = true;
		}

		if (feets >= 0 && feets <= 99999)
		{
			AltitudeFormatter formatter(unit);

			if (unit == UnitDisplayMode::Imperial)
			{
				str = formatter.StringFromAltitude(feets);
			}
			else if (unit == UnitDisplayMode::Metric)
			{
				str = formatter.StringFromAltitude(AltitudeConverter::FeetToMeter(feets));
			}
		}
		else
		{
			str = "INV";
		}

		return std::make_shared<StringContent>(CStringW(str), "", hasUnderline);
	}
}
