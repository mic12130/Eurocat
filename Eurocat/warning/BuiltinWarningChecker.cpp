#include "base/pch.h"

#include "warning/BuiltinWarningChecker.h"

#include "system/SystemManager.h"

namespace Eurocat::Warning
{
	void BuiltinWarningChecker::OnTimedEvent(int counter)
	{
		auto& plugin = SystemManager::Shared().GetPlugin();

		clamWarningTargetIds.clear();
		ramWarningTargetIds.clear();

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
				if (fp.GetCLAMFlag())
				{
					clamWarningTargetIds.push_back(rt.GetSystemID());
				}

				if (fp.GetRAMFlag())
				{
					ramWarningTargetIds.push_back(rt.GetSystemID());
				}
			}
		}
	}

	std::vector<CString> BuiltinWarningChecker::GetClamWarningTargetIds()
	{
		return clamWarningTargetIds;
	}

	std::vector<CString> BuiltinWarningChecker::GetRamWarningTargetIds()
	{
		return ramWarningTargetIds;
	}
}
