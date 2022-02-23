#include "base/pch.h"

#include "plugin/input/PopupMenu.h"

#include "plugin/input/EuroScopeInputBridge.h"

namespace Eurocat::Plugin::Input
{
	void PopupMenu::Show(POINT point, RECT rect)
	{
		if (auto manager = EuroScopeInputBridge::shared->GetEuroScopeInputManager().lock())
		{
			manager->OpenPopupList(rect, popupMenuTitle, shared_from_this());

			for (const auto& item : items)
			{
				manager->AddPopupListElement(item.text, item.selected);
			}
		}
	}

	void PopupMenu::AddItem(PopupMenuItem item)
	{
		items.push_back(item);
	}

	void PopupMenu::SetTitle(CString title)
	{
		popupMenuTitle = title;
	}

	void PopupMenu::OnRetrieveEuroScopeInput(CString str, POINT point, RECT rect)
	{
		for (const auto& item : items)
		{
			if (item.text == str)
			{
				if (auto d = delegate.lock())
				{
					d->OnSelectItem(item, point, rect);
				}

				break;
			}
		}
	}
}
