#include "base/pch.h"

#include "plugin/input/PopupEdit.h"

#include "plugin/input/EuroScopeInputBridge.h"

namespace Eurocat::Plugin::Input
{
	PopupEdit::PopupEdit(CString initialContent, bool isUpperCaseAll)
		: initialContent(initialContent), isUpperCaseAll(isUpperCaseAll)
	{
	}

	void PopupEdit::Show(POINT point, RECT rect)
	{
		if (auto manager = EuroScopeInputBridge::shared->GetEuroScopeInputManager().lock())
		{
			manager->OpenPopupEdit(rect, initialContent, shared_from_this());
		}
	}

	void PopupEdit::OnRetrieveEuroScopeInput(CString str, POINT point, RECT rect)
	{
		if (auto d = delegate.lock())
		{
			d->OnSubmit(str, point, rect);
		}
	}
}
