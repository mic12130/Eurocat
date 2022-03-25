#include "base/pch.h"

#include "plugin/extension/CflData.h"

namespace Eurocat::Plugin::Extension
{
	std::optional<int> Extension::CflData::GetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp)
	{
		int original = fp.GetControllerAssignedData().GetClearedAltitude();

		if (original == 1 || original == 2 || original == kNoneCflValue)
		{
			return std::nullopt;
		}

		return original;
	}

	int Extension::CflData::SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, std::optional<int> level)
	{
		return fp.GetControllerAssignedData().SetClearedAltitude(level.value_or(kNoneCflValue));
	}

	int Extension::CflData::SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, int level)
	{
		return SetForFlightPlan(fp, std::make_optional(level));
	}

	int Extension::CflData::SetNoneForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp)
	{
		return SetForFlightPlan(fp, std::nullopt);
	}
}
