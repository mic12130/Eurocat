#include "base/pch.h"

#include "system/SystemContainer.h"

Gdiplus::GdiplusStartupInput kGdiplusStartupInput;
ULONG_PTR kGdiplusToken;

void __declspec(dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Eurocat::SystemContainer::Shared().Startup();
	*ppPlugInInstance = &Eurocat::SystemContainer::Shared().GetPlugin();

	Gdiplus::GdiplusStartup(&kGdiplusToken, &kGdiplusStartupInput, NULL);
}

void __declspec(dllexport) EuroScopePlugInExit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Eurocat::SystemContainer::Shared().Cleanup();

	Gdiplus::GdiplusShutdown(kGdiplusToken);
}
