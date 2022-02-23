#include "base/pch.h"

#include "hmi/track/vel/VelRenderer.h"
#include "helper/CoordinateHelper.h"
#include "helper/GraphicsHelper.h"

using namespace Gdiplus;
using namespace Eurocat::Helper;

namespace Eurocat::Hmi::Track
{
	void VelRenderer::Render(IRadarTargetDataProvider& rt, const TrackProfile& profile, Gdiplus::Color color, int minutes, Screen::ScreenWrapper& screen, Screen::GraphicsWrapper& graphics)
	{
		double heading = rt.GetHeading();
		double oneMinuteDistance = rt.GetGroundSpeed() / 60.0;

		// Tests how many pixels per miles (Px/nm)
		POINT testPos1Px = { 100, 300 };
		POINT testPos2Px = { 500, 300 };
		EuroScopePlugIn::CPosition testPos1 = screen.ConvertCoordFromPixelToPosition(testPos1Px);
		EuroScopePlugIn::CPosition testPos2 = screen.ConvertCoordFromPixelToPosition(testPos2Px);
		double pixelsPerMiles = (testPos2Px.x - testPos1Px.x) / testPos1.DistanceTo(testPos2);

		// Get vector's origin and destination and render
		auto origin = rt.GetPosition();
		auto _originPx = screen.ConvertCoordFromPositionToPixel(CoordinateHelper::ConvertToCPosition(origin));
		PointF originPx(float(_originPx.x), float(_originPx.y));
		PointF destPx = GraphicsHelper::GetPolarPoint(originPx, heading, oneMinuteDistance * pixelsPerMiles * minutes);

		Pen pen(color, REAL(1));
		graphics.SetAntialias(true);
		graphics.DrawLine(originPx, destPx, pen);
		graphics.SetAntialias(false);
	}
}
