#include "base/pch.h"

#include "warning/BuiltinWarningChecker.h"

#include "plugin/PluginAccess.h"

using namespace Eurocat::Plugin;

namespace Eurocat::Warning
{
	void BuiltinWarningChecker::Check()
	{
		auto& plugin = PluginAccess::Shared().GetPlugin();
		std::vector<BuiltinWarning> newWarnings;

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
				bool isClam = fp.GetCLAMFlag();
				bool isRam = fp.GetRAMFlag();

				if (isClam || isRam)
				{
					newWarnings.push_back(BuiltinWarning(rt.GetSystemID(), isClam, isRam));
				}
			}
		}

		if (newWarnings != warnings)
		{
			if (newWarnings.empty())
			{
				spdlog::info("Built-in warnings changed: null");
			}
			else
			{
				std::string msg = "Built-in warnings changed:";
				for (auto& w : newWarnings) { msg += " (" + w.Description() + ")"; }
				spdlog::info(msg);
			}
		}

		warnings = newWarnings;
	}

	std::vector<BuiltinWarning> BuiltinWarningChecker::GetWarnings()
	{
		return warnings;
	}
}
