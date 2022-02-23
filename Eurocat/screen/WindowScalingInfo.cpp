#include "base/pch.h"

#include "screen/WindowScalingInfo.h"

namespace Eurocat::Screen
{
	double WindowScalingInfo::GetScaleFactor()
	{
		if (!isLoaded)
		{
			POINT ptZero = { 0, 0 };
			HMONITOR hMon = MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);

			MONITORINFOEX miex;
			miex.cbSize = sizeof(MONITORINFOEX);
			GetMonitorInfo(hMon, &miex);
			int cxLogical = miex.rcMonitor.right - miex.rcMonitor.left;

			DEVMODE dm;
			dm.dmSize = sizeof(DEVMODE);
			EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
			int cxPhysical = int(dm.dmPelsWidth);

			scaleFactor = double(cxPhysical) / double(cxLogical);
			isLoaded = true;
		}

		return scaleFactor;
	}
}
