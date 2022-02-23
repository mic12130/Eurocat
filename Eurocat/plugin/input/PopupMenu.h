#pragma once

#include "plugin/input/PopupMenuItem.h"
#include "plugin/input/PopupMenuDelegate.h"
#include "plugin/input/EuroScopeInputRetriever.h"

namespace Eurocat::Plugin::Input
{
	// The EuroScope popup menu
	// Has to be created as a shared pointer due to lifetime management
	class PopupMenu : public EuroScopeInputRetriever, public std::enable_shared_from_this<PopupMenu>
	{
	public:
		void Show(POINT point, RECT rect);
		void AddItem(PopupMenuItem item);
		void SetTitle(CString title);

		// Comply with EuroScopeInputRetriever
		void OnRetrieveEuroScopeInput(CString str, POINT point, RECT rect) override;

		std::weak_ptr<PopupMenuDelegate> delegate;

	private:
		std::vector<PopupMenuItem> items;
		CString popupMenuTitle = "";
	};
}
