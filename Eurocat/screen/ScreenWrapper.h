#pragma once

namespace Eurocat::Screen
{
	// Provides information related to the screen
	//
	// The main propose of creating this class is to hide the GetPlugIn() function
	// in the original EuroScopePlugIn::CRadarScreen, which allows bypassing
	// the plugin environment and accessing the plugin directly
	class ScreenWrapper
	{
	public:
		ScreenWrapper(EuroScopePlugIn::CRadarScreen& screen);
		RECT GetToolbarArea();
		RECT GetRadarArea();
		RECT GetChatArea();
		EuroScopePlugIn::CPosition ConvertCoordFromPixelToPosition(POINT pt);
		POINT ConvertCoordFromPositionToPixel(EuroScopePlugIn::CPosition pos);
		void AddScreenObject(
			int objectType, const char* objectId,
			RECT area, bool moveable, const char* message
		);
		void RequestRefresh(void);
		void StartTagFunction(
			const char* callsign, 
			const char* itemPlugInName, int itemCode, const char* itemString,
			const char* functionPlugInName, int functionId,
			POINT pt, RECT area
		);
		void GetDisplayArea(
			EuroScopePlugIn::CPosition* leftDown,
			EuroScopePlugIn::CPosition* rightUp
		);
		void SetDisplayArea(
			EuroScopePlugIn::CPosition leftDown,
			EuroScopePlugIn::CPosition rightUp
		);

	private:
		EuroScopePlugIn::CRadarScreen& screen;
	};
}
