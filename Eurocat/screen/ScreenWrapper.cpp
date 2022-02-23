#include "base/pch.h"

#include "screen/ScreenWrapper.h"

namespace Eurocat::Screen
{
	ScreenWrapper::ScreenWrapper(EuroScopePlugIn::CRadarScreen& screen)
		: screen(screen)
	{
	}

	RECT ScreenWrapper::GetToolbarArea()
	{
		return screen.GetToolbarArea();
	}

	RECT ScreenWrapper::GetRadarArea()
	{
		return screen.GetRadarArea();
	}

	RECT ScreenWrapper::GetChatArea()
	{
		return screen.GetChatArea();
	}

	EuroScopePlugIn::CPosition ScreenWrapper::ConvertCoordFromPixelToPosition(POINT pt)
	{
		return screen.ConvertCoordFromPixelToPosition(pt);
	}

	POINT ScreenWrapper::ConvertCoordFromPositionToPixel(EuroScopePlugIn::CPosition pos)
	{
		return screen.ConvertCoordFromPositionToPixel(pos);
	}

	void ScreenWrapper::AddScreenObject(int objectType, const char* objectId, RECT area, bool moveable, const char* message)
	{
		screen.AddScreenObject(objectType, objectId, area, moveable, message);
	}

	void ScreenWrapper::RequestRefresh()
	{
		screen.RequestRefresh();
	}

	void ScreenWrapper::StartTagFunction(
		const char* callsign, 
		const char* itemPlugInName, int itemCode, const char* itemString, 
		const char* functionPlugInName, int functionId, 
		POINT pt, RECT area)
	{
		screen.StartTagFunction(
			callsign, 
			itemPlugInName, itemCode, itemString, 
			functionPlugInName, functionId, 
			pt, area
		);
	}

	void ScreenWrapper::GetDisplayArea(EuroScopePlugIn::CPosition* leftDown, EuroScopePlugIn::CPosition* rightUp)
	{
		screen.GetDisplayArea(leftDown, rightUp);
	}

	void ScreenWrapper::SetDisplayArea(EuroScopePlugIn::CPosition leftDown, EuroScopePlugIn::CPosition rightUp)
	{
		screen.SetDisplayArea(leftDown, rightUp);
	}
}
