#pragma once

#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Unit
{
	// Manages the unit display mode of each flight plan or radar target
	// Notes: This is more likely to be a placeholder at this time
	// The position unit setting has to be implemented before we can move forward
	class UnitDisplayManager
	{
	public:
		UnitDisplayMode GetUnitForRadarTarget(CString targetId);
		void UpdateUnitForRadarTarget(CString targetId);
		UnitDisplayMode GetUnitForFlightPlan(CString callsign);
		void UpdateUnitForFlightPlan(CString callsign);
		UnitDisplayMode GetDefaultUnit();
		void SetDefaultUnit(UnitDisplayMode unit);

	private:
		UnitDisplayMode defaultUnit = UnitDisplayMode::Imperial;
		std::map<CString, UnitDisplayMode> unitMap;
	};
}
