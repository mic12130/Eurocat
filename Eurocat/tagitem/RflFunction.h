#pragma once

#include "plugin/IFunctionHandler.h"
#include "hmi/unit/UnitDisplayManager.h"
#include "window/LevelPopupMenuDelegate.h"

namespace Eurocat::TagItem
{
	class RflFunction : public Plugin::IFunctionHandler, public Window::LevelPopupMenuDelegate
	{
	public:
		RflFunction(Hmi::Unit::UnitDisplayManager& unitDisplayManager);
		void OnFunctionCall(int functionId, CString itemString, POINT point, RECT area) override;
		void OnSelectLevel(int level, Hmi::Unit::UnitDisplayMode unit) override;

	private:
		Hmi::Unit::UnitDisplayManager& unitDisplayManager;
		CString callsignForPopup;

		inline static std::map<int, int> kRflMeterToFeetMap = std::map<int, int>
		{
			{14900, 48900}, {14300, 46900}, {13700, 44900}, {13100, 43000},
			{12500, 41100}, {12200, 40100}, {11900, 39100}, {11600, 38100},
			{11300, 37100}, {11000, 36100}, {10700, 35100}, {10400, 34100},
			{10100, 33100}, {9800, 32100}, {9500, 31100}, {9200, 30100},
			{8900, 29100}, {8400, 27600}, {8100, 26600}, {7800, 25600},
			{7500, 24600}, {7200, 23600}, {6900, 22600}, {6600, 21700},
			{6300, 20700}, {6000, 19700}, {5700, 18700}, {5400, 17700},
			{5100, 16700}, {4800, 15700}, {4500, 14800}, {4200, 13800},
			{3900, 12800}, {3600, 11800}, {3300, 10800}, {3000, 9800},
			{2700, 8900}, {2400, 7900}, {2100, 6900}, {1800, 5900},
			{1500, 4900}, {1200, 3900}, {900, 3000}, {600, 2000},
			{300, 1000}, {0, 0}
		};
	};
}
