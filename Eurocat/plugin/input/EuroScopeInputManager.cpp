#include "base/pch.h"

#include "plugin/input/EuroScopeInputManager.h"

#include "plugin/PluginFunctionId.h"
#include "plugin/Plugin.h"
#include "plugin/input/EuroScopeInputBridge.h"

namespace Eurocat::Plugin::Input
{
	EuroScopeInputManager::EuroScopeInputManager(PluginEnvironment& pluginEnv) : pluginEnv(pluginEnv)
	{
	}

	void EuroScopeInputManager::OpenPopupEdit(RECT rect, CString initialValue, std::shared_ptr<EuroScopeInputRetriever> retriever)
	{
		currentRetriever = std::move(retriever);
		pluginEnv.GetPlugin().OpenPopupEdit(rect, PluginFunctionId::kSubmitInputFunctionId, initialValue);
	}

	void EuroScopeInputManager::OpenPopupList(RECT rect, CString title, std::shared_ptr<EuroScopeInputRetriever> retriever)
	{
		currentRetriever = std::move(retriever);
		pluginEnv.GetPlugin().OpenPopupList(rect, title, 1);
	}

	void EuroScopeInputManager::AddPopupListElement(CString str, bool selected)
	{
		pluginEnv.GetPlugin().AddPopupListElement(str, "", PluginFunctionId::kSubmitInputFunctionId, selected);
	}

	void EuroScopeInputManager::OnFunctionCall(int functionId, CString itemString, POINT point, RECT area)
	{
		currentRetriever->OnRetrieveEuroScopeInput(itemString, point, area);
	}
}
