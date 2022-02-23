#pragma once

#include "plugin/input/EuroScopeInputRetriever.h"
#include "plugin/IFunctionHandler.h"
#include "plugin/PluginEnvironment.h"

namespace Eurocat::Plugin
{
	class EurocatPlugin;
}

namespace Eurocat::Plugin::Input
{
	class EuroScopeInputManager : public IFunctionHandler
	{
	public:
		EuroScopeInputManager(PluginEnvironment& pluginEnv);
		void OpenPopupEdit(RECT rect, CString initialValue, std::shared_ptr<EuroScopeInputRetriever> retriever);
		void OpenPopupList(RECT rect, CString title, std::shared_ptr<EuroScopeInputRetriever> retriever);
		void AddPopupListElement(CString str, bool selected = false);
		void OnFunctionCall(int functionId, CString itemString, POINT point, RECT area) override;

	private:
		PluginEnvironment& pluginEnv;
		std::shared_ptr<EuroScopeInputRetriever> currentRetriever;
	};
}
