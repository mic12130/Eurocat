#include "base/pch.h"

#include "hmi/unit/UnitDisplayManager.h"

namespace Eurocat::Hmi::Unit
{
	UnitDisplayMode UnitDisplayManager::GetUnitForRadarTarget(CString targetId)
	{
		return defaultUnit;
	}

	void UnitDisplayManager::UpdateUnitForRadarTarget(CString targetId)
	{
	}

	UnitDisplayMode UnitDisplayManager::GetUnitForFlightPlan(CString callsign)
	{
		return defaultUnit;
	}

	void UnitDisplayManager::UpdateUnitForFlightPlan(CString callsign)
	{
	}

	UnitDisplayMode UnitDisplayManager::GetDefaultUnit()
	{
		return defaultUnit;
	}

	void UnitDisplayManager::SetDefaultUnit(UnitDisplayMode unit)
	{
		defaultUnit = unit;
	}
}
