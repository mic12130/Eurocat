#include "base/pch.h"

#include "hmi/track/action/AcidActionHandler.h"

#include "hmi/cursor/CursorManager.h"
#include "hmi/track/action/EuroScopeFunctionHelper.h"
#include "hmi/track/tag/render_data/ExtendedLabelCalc.h"
#include "hmi/track/FlightPlanDataProvider.h"
#include "plugin/PluginAccess.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Screen;
using namespace Eurocat::Hmi::Cursor;
using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	AcidActionHandler::AcidActionHandler(TrackProfileManager& trackProfileManager, OptionData& option)
		: trackProfileManager(trackProfileManager), option(option)
	{
	}

	void AcidActionHandler::OnTriggerAction(
		const TrackProfile& trackProfile,
		Screen::ScreenWrapper& screen,
		Screen::MouseButton button,
		POINT point, RECT area)
	{
		if (button == MouseButton::Left)
		{
			EuroScopeFunctionHelper::CallEsFunction(
				trackProfile.flightPlanId.value(),
				EuroScopePlugIn::TAG_ITEM_FUNCTION_OPEN_FP_DIALOG,
				point, area, screen
			);
		}
		else if (button == MouseButton::Middle)
		{
			TrackProfile updatedTrackProfile(trackProfile);
			auto fp = PluginAccess::Shared().GetPlugin().FlightPlanSelect(trackProfile.flightPlanId.value());
			auto fpProvider = FlightPlanDataProvider(fp);

			// Whether the tag would be extended if no user-set extended behaviour was stored (null)
			// We will perform operation based on this value
			bool extendedByDefault = ExtendedLabelCalc::RendersExtendedLabel(option, fpProvider, trackProfile);

			if (trackProfile.userSetExtended.has_value())
			{
				if (trackProfile.userSetExtended == extendedByDefault)
				{
					updatedTrackProfile.userSetExtended = !extendedByDefault;
				}
				else
				{
					updatedTrackProfile.userSetExtended = std::nullopt;
				}
			}
			else
			{
				updatedTrackProfile.userSetExtended = !extendedByDefault;
			}

			trackProfileManager.TryUpdateProfile(updatedTrackProfile);
		}
		else if (button == MouseButton::Right)
		{
			EuroScopeFunctionHelper::CallEsFunction(
				trackProfile.flightPlanId.value(),
				EuroScopePlugIn::TAG_ITEM_FUNCTION_HANDOFF_POPUP_MENU,
				point, area, screen
			);
		}
	}
}
