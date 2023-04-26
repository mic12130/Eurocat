#include "base/pch.h"

#include "warning/DupeSquawkChecker.h"

#include "warning/DupeSquawkCheckDataProvider.h"

namespace Eurocat::Warning
{
	DupeSquawkChecker::DupeSquawkChecker(std::shared_ptr<IDupeSquawkCheckDataProvider> dataProvider)
		: dataProvider(std::move(dataProvider))
	{
	}

	DupeSquawkChecker::DupeSquawkChecker()
		: dataProvider(std::make_shared<DupeSquawkCheckDataProvider>())
	{
	}

	void DupeSquawkChecker::Check()
	{
		std::map<CString, std::vector<CString>> targetIdsBySquawk;
		warnings.clear();

		for (auto& squawkData : dataProvider->GetSquawkDataCollection())
		{
			auto it = targetIdsBySquawk.find(squawkData.squawk);

			if (it != targetIdsBySquawk.end())
			{
				auto targetIds = it->second;
				targetIds.push_back(squawkData.targetId);
				it->second = targetIds;
			}
			else
			{
				targetIdsBySquawk[squawkData.squawk] = { squawkData.targetId };
			}
		}

		for (const auto& it : targetIdsBySquawk)
		{
			if (it.second.size() > 1)
			{
				warnings.emplace_back(it.first, it.second);
			}
		}
	}

	std::vector<DupeWarning> DupeSquawkChecker::GetWarnings()
	{
		return warnings;
	}
}
