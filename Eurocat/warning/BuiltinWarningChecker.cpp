#include "base/pch.h"

#include "warning/BuiltinWarningChecker.h"

#include "plugin/PluginAccess.h"

using namespace Eurocat::Plugin;

namespace Eurocat::Warning
{
	void BuiltinWarningChecker::OnTimedEvent(int counter)
	{
		auto& plugin = PluginAccess::Shared().GetPlugin();

		warnings.clear();

		for (auto rt = plugin.RadarTargetSelectFirst();
			rt.IsValid();
			rt = plugin.RadarTargetSelectNext(rt))
		{
			if (!rt.GetPosition().GetTransponderC())
			{
				continue;
			}

			if (auto fp = rt.GetCorrelatedFlightPlan(); fp.IsValid())
			{
				warnings.push_back(BuiltinWarning(rt.GetSystemID(), fp.GetCLAMFlag(), fp.GetRAMFlag()));
			}
		}
	}

	std::vector<BuiltinWarning> BuiltinWarningChecker::GetWarnings()
	{
		return warnings;
	}
}
