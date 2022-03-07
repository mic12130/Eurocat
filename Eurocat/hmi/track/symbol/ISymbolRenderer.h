#pragma once

#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/symbol/SymbolObjectInfo.h"

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
			const SymbolObjectInfo& info
		) = 0;
	};
}
