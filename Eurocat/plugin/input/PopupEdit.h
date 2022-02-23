#pragma once

#include "plugin/input/EuroScopeInputRetriever.h"
#include "plugin/input/PopupEditDelegate.h"

namespace Eurocat::Plugin::Input
{
	// The EuroScope popup edit
	// Has to be created as a shared pointer due to lifetime management
	class PopupEdit : public EuroScopeInputRetriever, public std::enable_shared_from_this<PopupEdit>
	{
	public:
		PopupEdit(CString initialContent, bool isUpperCaseAll = false);
		void Show(POINT point, RECT rect);

		// Comply with EuroScopeInputRetriever
		void OnRetrieveEuroScopeInput(CString str, POINT point, RECT rect) override;

		std::weak_ptr<PopupEditDelegate> delegate;

	private:
		CString initialContent;
		bool isUpperCaseAll;
	};
}
