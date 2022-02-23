#include "base/pch.h"

#include "screen/Screen.h"

#include "hmi/cursor/CursorManager.h"

using namespace Eurocat::Hmi::Cursor;

namespace Eurocat::Screen
{
	EurocatScreen::EurocatScreen(std::vector<std::shared_ptr<IScreenEventHandler>>& screenEventHandlers)
		: screenEventHandlers(screenEventHandlers)
	{
	}

	void EurocatScreen::OnAsrContentToBeClosed()
	{
		CursorManager::shared->OnScreenToBeClosed();
		delete this;
	}

	void EurocatScreen::OnRefresh(HDC hDC, int Phase)
	{
		Gdiplus::Graphics graphics(hDC);
		GraphicsWrapper graphicsWrapper(graphics);
		ScreenWrapper screenWrapper(*this);

		if (Phase == EuroScopePlugIn::REFRESH_PHASE_AFTER_TAGS)
		{
			CursorManager::shared->OnRender();

			for (const auto& handler : screenEventHandlers)
			{
				handler->OnRender(screenWrapper, graphicsWrapper);
			}
		}
	}

	void EurocatScreen::OnOverScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area)
	{
		ScreenWrapper screenWrapper(*this);
		MouseInputArgs args(ObjectType, sObjectId, Pt, Area, MouseButton::None);

		for (const auto& handler : screenEventHandlers)
		{
			handler->OnOverScreenObject(screenWrapper, args);
		}
	}

	void EurocatScreen::OnClickScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button)
	{
		MouseButton button = MouseButton::None;

		switch (Button)
		{
		case EuroScopePlugIn::BUTTON_LEFT:
			button = MouseButton::Left;
			break;
		case EuroScopePlugIn::BUTTON_RIGHT:
			button = MouseButton::Right;
			break;
		case EuroScopePlugIn::BUTTON_MIDDLE:
			button = MouseButton::Middle;
			break;
		default:
			break;
		}

		ScreenWrapper screenWrapper(*this);
		MouseInputArgs args(ObjectType, sObjectId, Pt, Area, button);

		for (const auto& handler : screenEventHandlers)
		{
			handler->OnClickScreenObject(screenWrapper, args);
		}
	}

	void EurocatScreen::OnMoveScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, bool Released)
	{
		ScreenWrapper screenWrapper(*this);
		MouseInputArgs args(ObjectType, sObjectId, Pt, Area, MouseButton::None, Released);

		for (const auto& handler : screenEventHandlers)
		{
			handler->OnMoveScreenObject(screenWrapper, args);
		}
	}
}
