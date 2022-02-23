#include "base/pch.h"

#include "hmi/track/tag/label/FlightRuleIndicator.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	FlightRuleIndicator::FlightRuleIndicator(IFlightPlanDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> FlightRuleIndicator::GetTagLabelContent()
	{
		// - "V" for VFR
		// - "Y" for IFR-VFR
		// - "Z" for VFR-IFR
		//
		// Or for IFR:
		// - "X" if the flight is non-RVSM-capable
		// - Blank if the flight is RVSM-capable
		//
		// In Eurocat-X, the system verifies the RVSM capability
		// by checking if "W" is included in filed 10a.
		// However, VATSIM merged field 10a and 10b into a single-char suffix.
		// (https://www.vatsim.net/pilot-resource-centre/general-lessons/choosing-equipment-code)
		// So in the plugin, we will verify the RVSM capability by checking
		// if the suffix is one of the suffixes indicating RVSM-capable
		// listed in the page above ("H", "W", "Z", "L")

		CString rule = data.GetFlightPlanType();
		CString str;

		if (rule == "V")
		{
			str = "V";
		}
		else if (rule == "Y")
		{
			str = "Y";
		}
		else if (rule == "Z")
		{
			str = "Z";
		}
		else if (rule == "I")
		{
			// Verify RVSM capability by checking the suffix

			char suffix = data.GetCapabilities();
			std::vector<char> capableSuffixes = { 'H', 'W', 'Z', 'L' };

			if (std::find(capableSuffixes.begin(), capableSuffixes.end(),
			              suffix) != capableSuffixes.end())
			{
				str = " ";
			}
			else
			{
				str = "X";
			}
		}
		else
		{
			// Unhandled flight rules
			str = " ";
		}

		return std::make_shared<StringContent>(str);
	}
}
