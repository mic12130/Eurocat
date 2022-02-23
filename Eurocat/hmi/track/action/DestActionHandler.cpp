#include "base/pch.h"

#include "hmi/track/action/DestActionHandler.h"

#include "hmi/track/action/EuroScopeFunctionHelper.h"

using namespace Eurocat::Screen;

namespace Eurocat::Hmi::Track
{
	void DestActionHandler::OnTriggerAction(
		const TrackProfile& trackProfile,
		Screen::ScreenWrapper& screen,
		Screen::MouseButton button,
		POINT point, RECT area)
	{
		if (button == MouseButton::Left)
		{
			EuroScopeFunctionHelper::CallEsFunction(
				trackProfile.flightPlanId.value(),
				EuroScopePlugIn::TAG_ITEM_FUNCTION_TOGGLE_ROUTE_DRAW,
				point, area, screen
			);
		}
	}
}
