#include "base/pch.h"

#include "window/LevelPopupMenu.h"

#include "common/unit/AltitudeFormatter.h"

using namespace Eurocat::Common::Unit;
using namespace Eurocat::Plugin::Input;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Window
{
	LevelPopupMenu::LevelPopupMenu(std::optional<int> currentLevel, Hmi::Unit::UnitDisplayMode unit)
		: unit(unit)
	{
		AltitudeFormatter formatter(unit);
		std::vector<int> levels;

		if (unit == UnitDisplayMode::Imperial)
		{
			levels = kImperialValues;
		}
		else if (unit == UnitDisplayMode::Metric)
		{
			levels = kMetricValues;
		}

		for (auto& level : levels)
		{
			CString str = formatter.StringFromAltitude(level);
			AddItem(PopupMenuItem(str, abs(level - currentLevel.value_or(-999)) < 100));
		}

		AddItem(PopupMenuItem("NONE", currentLevel.has_value() == false));
	}

	void LevelPopupMenu::OnRetrieveEuroScopeInput(CString str, POINT point, RECT rect)
	{
		PopupMenu::OnRetrieveEuroScopeInput(str, point, rect);

		if (str == "NONE")
		{
			if (auto d = levelPopupDelegate.lock())
			{
				d->OnSelectLevel(std::nullopt, unit);
			}

			return;
		}

		int level = 0;

		if (unit == UnitDisplayMode::Imperial)
		{
			level = std::stoi(str.GetString()) * 100;
		}
		else if (unit == UnitDisplayMode::Metric)
		{
			level = std::stoi(str.GetString()) * 10;
		}

		if (auto d = levelPopupDelegate.lock())
		{
			d->OnSelectLevel(level, unit);
		}
	}
}
