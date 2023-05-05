#include "base/pch.h"

#include "warning/DupeSquawkChecker.h"

namespace Eurocat::Warning
{
	DupeSquawkChecker::DupeSquawkChecker(std::shared_ptr<ICheckableDataProvider> dataProvider)
		: dataProvider(std::move(dataProvider))
	{
	}

	void DupeSquawkChecker::Check()
	{
		std::map<CString, std::vector<CString>> targetIdsBySquawk;
		std::vector<DupeWarning> newWarnings;

		for (auto& rt : dataProvider->GetRadarTargets())
		{
			auto it = targetIdsBySquawk.find(rt.squawk);

			if (it != targetIdsBySquawk.end())
			{
				auto targetIds = it->second;
				targetIds.push_back(rt.targetId);
				it->second = targetIds;
			}
			else
			{
				targetIdsBySquawk[rt.squawk] = { rt.targetId };
			}
		}

		for (const auto& it : targetIdsBySquawk)
		{
			if (it.second.size() > 1)
			{
				newWarnings.emplace_back(it.first, it.second);
			}
		}

		std::lock_guard<std::mutex> lock(m);
		if (newWarnings != warnings)
		{
			if (newWarnings.empty())
			{
				spdlog::info("DUPE warnings changed: null");
			}
			else
			{
				std::string msg = "DUPE warnings changed:";
				for (auto& w : newWarnings) { msg += " (" + w.Description() + ")"; }
				spdlog::info(msg);
			}
		}

		warnings = newWarnings;
	}

	std::vector<DupeWarning> DupeSquawkChecker::GetWarnings()
	{
		std::lock_guard<std::mutex> lock(m);
		return warnings;
	}
}
