#include "base/pch.h"

#include "system/SystemManager.h"

Gdiplus::GdiplusStartupInput kGdiplusStartupInput;
ULONG_PTR kGdiplusToken;

void __declspec(dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Eurocat::SystemManager::Shared().Startup();
	*ppPlugInInstance = &Eurocat::SystemManager::Shared().GetPlugin();

	Gdiplus::GdiplusStartup(&kGdiplusToken, &kGdiplusStartupInput, NULL);
}

void __declspec(dllexport) EuroScopePlugInExit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Eurocat::SystemManager::Shared().Cleanup();

	Gdiplus::GdiplusShutdown(kGdiplusToken);
}
