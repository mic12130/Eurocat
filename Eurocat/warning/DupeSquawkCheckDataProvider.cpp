#include "base/pch.h"

#include "warning/DupeSquawkCheckDataProvider.h"

#include "system/SystemManager.h"

using namespace Eurocat::Plugin;

namespace Eurocat::Warning
{
	std::vector<SquawkData> DupeSquawkCheckDataProvider::GetSquawkDataCollection()
	{
		auto& plugin = SystemManager::Shared().GetPlugin();
		std::vector<SquawkData> result;

		for (auto rt = plugin.RadarTargetSelectFirst();
			rt.IsValid();
			rt = plugin.RadarTargetSelectNext(rt))
		{
			if (!rt.GetPosition().GetTransponderC())
			{
				continue;
			}

			result.emplace_back(rt.GetSystemID(), rt.GetPosition().GetSquawk());
		}

		return result;
	}
}
