#pragma once

#include "plugin/IFunctionHandler.h"
#include "hmi/unit/UnitDisplayManager.h"
#include "window/LevelPopupMenuDelegate.h"

namespace Eurocat::TagItem
{
	class CflFunction : public Plugin::IFunctionHandler, public Window::LevelPopupMenuDelegate
	{
	public:
		CflFunction(Hmi::Unit::UnitDisplayManager& unitDisplayManager);
		void OnFunctionCall(int functionId, CString itemString, POINT point, RECT area) override;
		void OnSelectLevel(int level, Hmi::Unit::UnitDisplayMode unit) override;

	private:
		Hmi::Unit::UnitDisplayManager& unitDisplayManager;
		CString callsignForPopup;
	};
}
