#include "base/pch.h"

#include "hmi/track/symbol/SymbolRenderController.h"

#include "hmi/track/FlashHelper.h"
#include "hmi/track/symbol/SymbolRenderer.h"
#include "hmi/track/TrackColor.h"
#include "hmi/track/TrackObjectId.h"
#include "hmi/track/TrackObjectIdSuffix.h"

namespace Eurocat::Hmi::Track
{
	SymbolRenderController::SymbolRenderController(Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
		: SymbolRenderController(std::make_shared<SymbolRenderer>(screen, graphics), FlashHelper::Regular())
	{
	}

	SymbolRenderController::SymbolRenderController(std::shared_ptr<ISymbolRenderer> renderer, std::shared_ptr<IFlashHelper> flashHelper)
		: renderer(std::move(renderer)), flashHelper(std::move(flashHelper))
	{
	}

	void SymbolRenderController::OnRenderSsrTrack(IRadarTargetDataProvider& rt, Gdiplus::Color color, const OptionData& option, bool isSelected, CString trackProfileId)
	{
		auto ssrSymbolColor = (rt.IsModeI() && flashHelper->ShouldRender()) ? TrackColor::kCyan : color;

		renderer->RenderSsrSymbol(rt.GetPosition(), ssrSymbolColor);

		if (option.hidePsrSymbol == false)
		{
			renderer->RenderPsrSymbol(rt.GetPosition(), color);
		}

		if (isSelected)
		{
			renderer->RenderSelectedSymbol(rt.GetPosition(), color);
		}

		renderer->AddScreenObject(
			rt.GetPosition(),
			TrackObjectId::Generate(trackProfileId, TrackObjectIdSuffix::kSymbol),
			""
		);
	}

	void SymbolRenderController::OnRenderPsrTrack(IRadarTargetDataProvider& rt, Gdiplus::Color color, const OptionData& option)
	{
		// We will not validate option.hidePsrSymbol here
		// Instead, it should be done before this controller's owner calling this function
		renderer->RenderPsrSymbol(rt.GetPosition(), color);
	}

	void SymbolRenderController::OnRenderGroundTrack(IRadarTargetDataProvider& rt, const CString& callsign, Gdiplus::Color color)
	{
		CString msg;
		msg.Format("%s [GROUND]", callsign.GetString());
		renderer->RenderGroundTrackSymbol(rt.GetPosition(), color);
		renderer->AddScreenObject(rt.GetPosition(), TrackObjectId::kNoActionObjectId, msg);
	}

	void SymbolRenderController::OnRenderFlightPlanTrack(IFlightPlanDataProvider& fp, Gdiplus::Color color, bool isSelected, CString trackProfileId)
	{
		renderer->RenderFlightPlanTrackSymbol(fp.GetFlightPlanTrackPosition(), color);

		if (isSelected)
		{
			renderer->RenderSelectedSymbol(fp.GetFlightPlanTrackPosition(), color);
		}

		renderer->AddScreenObject(
			fp.GetFlightPlanTrackPosition(),
			TrackObjectId::Generate(trackProfileId, TrackObjectIdSuffix::kSymbol),
			""
		);
	}
}
