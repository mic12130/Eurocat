#pragma once

#include "screen/IScreenEventHandler.h"
#include "hmi/unit/UnitDisplayManager.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/profile/TrackProfileManager.h"
#include "hmi/track/option/OptionData.h"
#include "hmi/track/symbol/SymbolRenderController.h"
#include "hmi/track/action/ITrackActionHandler.h"
#include "hmi/track/RenderableTrack.h"

namespace Eurocat::Plugin
{
	class EurocatPlugin;
}

namespace Eurocat::Hmi::Track
{
	class TrackManager : public Screen::IScreenEventHandler
	{
	public:
		TrackManager(Unit::UnitDisplayManager& unitDisplayManager);
		void OnRender(Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics) override;
		void OnOverScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args) override;
		void OnClickScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args) override;
		void OnMoveScreenObject(Screen::ScreenWrapper& screen, Screen::MouseInputArgs& args) override;
		OptionData& GetOption();
		TrackProfileManager& GetTrackProfileManager();

	private:
		void RenderTracks(
			std::vector<RenderableTrack>& tracks, 
			Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics);
		bool InRange(POINT px, RECT rect);
		bool IsSelected(IRadarTargetDataProvider& rt);
		bool IsSelected(IFlightPlanDataProvider& fp);
		bool IsAboveTransAltitude(IRadarTargetDataProvider& rt);
		auto GetUnit(IRadarTargetDataProvider& rt) -> Hmi::Unit::UnitDisplayMode;
		auto GetUnit(IFlightPlanDataProvider& fp) -> Hmi::Unit::UnitDisplayMode;
		void FinishTagReposition(Screen::ScreenWrapper& screen);

		const int kGroundTrafficMaxSpeed = 30;

		TrackProfileManager trackProfileManager;
		OptionData option;
		Hmi::Unit::UnitDisplayManager& unitDisplayManager;
		std::optional<CString> repositioningProfileId;
		std::map<CString, std::shared_ptr<ITrackActionHandler>> actionHandlerMap;
	};
}
