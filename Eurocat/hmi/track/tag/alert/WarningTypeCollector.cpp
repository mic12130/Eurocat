#include "base/pch.h"

#include "hmi/track/tag/alert/WarningTypeCollector.h"

#include "warning/WarningData.h"

using namespace Eurocat::Warning;

namespace Eurocat::Hmi::Track
{
	std::vector<WarningType> WarningTypeCollector::GetWarningTypes(CString targetId)
	{
		auto builtinWarnings = WarningData::Shared().GetBuiltinWarnings();
		auto dupeWarnings = WarningData::Shared().GetDupeWarnings();
		std::vector<WarningType> result;

		for (auto& w : builtinWarnings)
		{
			if (w.targetId == targetId)
			{
				if (w.isClam)
					result.push_back(WarningType::Clam);
				else if (w.isRam)
					result.push_back(WarningType::Ram);

				break;
			}
		}

		for (auto& w : dupeWarnings)
		{
			auto& targetIds = w.targetIds;

			if (std::find(targetIds.begin(), targetIds.end(), targetId) != targetIds.end())
			{
				result.push_back(WarningType::Dupe);
				break;
			}
		}

		return std::vector<WarningType>();
	}
}