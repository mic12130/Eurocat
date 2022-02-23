#pragma once

#include "hmi/track/action/ITrackActionHandler.h"

namespace Eurocat::Hmi::Track
{
	class DestActionHandler : public ITrackActionHandler
	{
	public:
		void OnTriggerAction(
			const TrackProfile& trackProfile,
			Screen::ScreenWrapper& screen,
			Screen::MouseButton button,
			POINT point, RECT area
		) override;
	};
}
