#pragma once

#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "screen/ScreenWrapper.h"
#include "screen/GraphicsWrapper.h"
#include "hmi/track/IFlashHelper.h"

namespace Eurocat::Hmi::Track
{
	class ISymbolRenderer
	{
	public:
		virtual ~ISymbolRenderer() = default;
		virtual void RenderSsrSymbol(
			Common::Coordinate coord,
			Gdiplus::Color color
		) = 0;
		virtual void RenderPsrSymbol(
			Common::Coordinate coord,
			Gdiplus::Color color
		) = 0;
		virtual void RenderGroundTrackSymbol(
			Common::Coordinate coord,
			Gdiplus::Color color
		) = 0;
		virtual void RenderFlightPlanTrackSymbol(
			Common::Coordinate coord,
			Gdiplus::Color color
		) = 0;
		virtual void RenderSelectedSymbol(
			Common::Coordinate coord,
			Gdiplus::Color color
		) = 0;
		virtual void AddScreenObject(
			Common::Coordinate coord, 
			CString objectId, 
			CString message
		) = 0;
	};
}
