#include "base/pch.h"

#include "hmi/track/tag/alert/WarningSelector.h"

namespace Eurocat::Hmi::Track
{
	std::optional<WarningType> WarningSelector::SelectWarning(std::vector<WarningType>& warnings)
	{
		std::vector orderList = {
			WarningType::Stca,
			WarningType::Daiw,
			WarningType::Msaw,
			WarningType::Clam,
			WarningType::Ram,
			WarningType::Dupe
		};

		if (warnings.empty() == false)
		{
			std::vector<WarningType> sorted;

			for (WarningType temp : orderList)
			{
				if (std::find(warnings.begin(), warnings.end(), temp) != warnings.end())
				{
					sorted.push_back(temp);
				}
			}

			if (sorted.size() != warnings.size())
			{
				throw std::runtime_error("The warning order list does not contain all input warnings");
			}

			for (WarningType temp : sorted)
			{
				// Returns the first sorted warning that in the allowed list
				if (std::find(allowedWarnings.begin(), allowedWarnings.end(), temp) != allowedWarnings.end())
				{
					return std::make_optional(temp);
				}
			}
		}

		return std::nullopt;
	}
}
