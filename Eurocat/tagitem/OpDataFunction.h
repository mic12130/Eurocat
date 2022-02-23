#pragma once

#include "plugin/IFunctionHandler.h"
#include "plugin/input/PopupEditDelegate.h"

namespace Eurocat::TagItem
{
	class OpDataFunction : public Plugin::IFunctionHandler, public Plugin::Input::PopupEditDelegate
	{
	public:
		void OnFunctionCall(int functionId, CString itemString, POINT point, RECT area) override;
		void OnSubmit(CString str, POINT point, RECT rect) override;

	private:
		CString flightPlanCallsignForPopup = "";
	};
}
