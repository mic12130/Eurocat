#include "base/pch.h"

#include "hmi/cursor/CursorManager.h"

#include "res/resource.h"

HCURSOR cursor;
WNDPROC sourceProc;
HWND window;

namespace Eurocat::Hmi::Cursor
{
	HCURSOR cursor;
	WNDPROC sourceProc;
	HWND window;

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_SETCURSOR)
		{
			SetCursor(cursor);
			return true;
		}

		return CallWindowProc(sourceProc, hwnd, uMsg, wParam, lParam);
	}

	std::shared_ptr<CursorManager> CursorManager::shared = std::make_shared<CursorManager>();

	void CursorManager::OnRender()
	{
		if (!isInitialized)
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState())

			if (cursor == nullptr)
			{
				cursor = AfxGetApp()->LoadCursor(IDC_CURSOR_NORMAL);
			}

			window = GetActiveWindow();
			sourceProc = WNDPROC(SetWindowLong(window, GWL_WNDPROC, (LONG)WindowProc));

			isInitialized = true;
		}
	}

	void CursorManager::OnScreenToBeClosed()
	{
		if (cursor != nullptr)
		{
			SetWindowLong(window, GWL_WNDPROC, (LONG)sourceProc);
		}

		isInitialized = false;
	}

	void CursorManager::SetCursorType(CursorType type)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())

		switch (type)
		{
		case CursorType::Normal:
			cursor = AfxGetApp()->LoadCursor(IDC_CURSOR_NORMAL);
			break;
		case CursorType::Interactive:
			cursor = AfxGetApp()->LoadCursor(IDC_CURSOR_INTERACTIVE);
			break;
		}

		SetCursor(cursor);
	}
}
