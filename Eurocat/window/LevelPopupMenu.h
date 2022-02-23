#pragma once

#include "plugin/input/PopupMenu.h"
#include "hmi/unit/UnitDisplayMode.h"
#include "window/LevelPopupMenuDelegate.h"

namespace Eurocat::Window
{
	class LevelPopupMenu : public Plugin::Input::PopupMenu
	{
	public:
		LevelPopupMenu(int currentLevel, Hmi::Unit::UnitDisplayMode unit);
		void OnRetrieveEuroScopeInput(CString str, POINT point, RECT rect) override;

		// Set this instead of the original PopupMenu::delegate
		std::weak_ptr<LevelPopupMenuDelegate> levelPopupDelegate;

	private:
		Hmi::Unit::UnitDisplayMode unit;
		
		const std::vector<int> kMetricValues = { 14900, 14300, 13700, 13100,
			12500, 12200, 11900, 11600, 11300, 11000, 10700, 10400, 10100,
			9800, 9500, 9200, 8900, 8400, 8100, 7800, 7500, 7200,
			6900, 6600, 6300, 6000, 5700, 5400, 5100, 4800, 4500,
			4200, 3900, 3600, 3300, 3000, 2700, 2400, 2100, 1800,
			1500, 1200, 900, 600, 300, 0 };
		const std::vector<int> kImperialValues = { 49000, 47000, 45000, 43000,
			41000, 40000, 39000, 38000, 37000, 36000, 35000, 34000, 33000,
			32000, 31000, 30000, 29000, 28000, 27000, 26000, 25000, 24000,
			23000, 22000, 21000, 20000, 19000, 18000, 17000, 16000, 15000,
			14000, 13000, 12000, 11000, 10000, 9000, 8000, 7000, 6000,
			5000, 4000, 3000, 2000, 1000, 0 };
	};
}
