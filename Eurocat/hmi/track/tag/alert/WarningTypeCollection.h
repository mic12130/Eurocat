#pragma once

#include "base/pch.h"

#include "warning/RadarTargetWarningInfo.h"
#include "hmi/track/tag/alert/WarningType.h"

namespace Eurocat::Hmi::Track
{
	class WarningTypeCollection
	{
	public:
		void AddFromRadarTargetWarningInfo(Warning::RadarTargetWarningInfo info)
		{
			if (info.isClam)
			{
				warningTypes.push_back(WarningType::Clam);
			}

			if (info.isRam)
			{
				warningTypes.push_back(WarningType::Ram);
			}

			if (info.isDupe)
			{
				warningTypes.push_back(WarningType::Dupe);
			}
		}

		std::vector<WarningType>& GetWaningTypes()
		{
			return warningTypes;
		}

	private:
		std::vector<WarningType> warningTypes;
	};
}
