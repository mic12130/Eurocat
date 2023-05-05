#include "base/pch.h"

#include "warning/CheckableDataProvider.h"

#include "plugin/PluginAccess.h"

using namespace Eurocat::Plugin;

namespace Eurocat::Warning
{
	std::vector<CheckableRadarTarget> CheckableDataProvider::GetRadarTargets()
	{
		std::shared_lock<std::shared_mutex> lock(m);
		return elements;
	}

	void CheckableDataProvider::UpdateFromPlugin()
	{
		auto& plugin = PluginAccess::Shared().GetPlugin();
		std::vector<CheckableRadarTarget> result;

		for (auto rt = plugin.RadarTargetSelectFirst();
			rt.IsValid();
			rt = plugin.RadarTargetSelectNext(rt))
		{
			if (!rt.GetPosition().GetTransponderC())
			{
				continue;
			}

			result.emplace_back(rt);
		}

		std::unique_lock<std::shared_mutex> lock(m);
		elements = result;
	}
}
