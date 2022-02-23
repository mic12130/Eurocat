#pragma once

#include "hmi/track/tag/alert/WarningType.h"

namespace Eurocat::Hmi::Track
{
	// Get the warning that has the highest priority
	class WarningSelector
	{
	public:
		std::optional<WarningType> SelectWarning(std::vector<WarningType>& warnings);

		// Contains all warnings by default
		std::vector<WarningType> allowedWarnings = std::vector<WarningType>
		{
			WarningType::Stca,
			WarningType::Daiw,
			WarningType::Msaw,
			WarningType::Clam,
			WarningType::Ram,
			WarningType::Dupe
		};
	};
}
