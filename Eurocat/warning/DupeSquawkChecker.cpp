#include "base/pch.h"

#include "warning/DupeSquawkChecker.h"

#include "warning/DupeSquawkCheckDataProvider.h"

namespace Eurocat::Warning
{
	DupeSquawkChecker::DupeSquawkChecker(std::unique_ptr<IDupeSquawkCheckDataProvider> dataProvider)
		: dataProvider(std::move(dataProvider))
	{
	}

	DupeSquawkChecker::DupeSquawkChecker()
		: dataProvider(std::make_unique<DupeSquawkCheckDataProvider>())
	{
	}

	void DupeSquawkChecker::Check()
	{
		auto squawkDataCollection = dataProvider->GetSquawkDataCollection();
		warningTargetIds.clear();

		for (unsigned i = 0; i < squawkDataCollection.size() - 1; i++)
		{
			for (unsigned j = i + 1; j < squawkDataCollection.size(); j++)
			{
				auto sourceData = squawkDataCollection[i];
				auto targetData = squawkDataCollection[j];

				if (sourceData.squawk == targetData.squawk)
				{
					if (std::find(warningTargetIds.begin(), warningTargetIds.end(), sourceData.targetId) == warningTargetIds.end())
					{
						warningTargetIds.push_back(sourceData.targetId);
					}
					
					if (std::find(warningTargetIds.begin(), warningTargetIds.end(), targetData.targetId) == warningTargetIds.end())
					{
						warningTargetIds.push_back(targetData.targetId);
					}
				}
			}
		}
	}

	std::vector<CString> DupeSquawkChecker::GetWarningTargetIds()
	{
		return warningTargetIds;
	}
}
