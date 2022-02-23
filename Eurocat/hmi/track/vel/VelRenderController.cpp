#include "base/pch.h"

#include "hmi/track/vel/VelRenderController.h"

#include "hmi/track/vel/VelRenderer.h"

namespace Eurocat::Hmi::Track
{
	VelRenderController::VelRenderController() : VelRenderController(std::make_shared<VelRenderer>())
	{
	}

	VelRenderController::VelRenderController(std::shared_ptr<IVelRenderer> renderer) : renderer(std::move(renderer))
	{
	}

	void VelRenderController::OnRenderSsrTrack(IRadarTargetDataProvider& rt, const TrackProfile& profile, const OptionData& option, Gdiplus::Color color, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		// User-set VEL configuration takes precedence over the global one
		if (profile.userSetVel.has_value())
		{
			if (profile.userSetVel.value() == false)
			{
				return;
			}
		}
		else if (option.enableVelocityVectorDisplay == false)
		{
			return;
		}

		renderer->Render(rt, profile, color, option.velocityVectorMinutes, screen, graphics);
	}
}
