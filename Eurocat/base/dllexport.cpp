#include "base/pch.h"

#include "system/SystemContainer.h"

Gdiplus::GdiplusStartupInput kGdiplusStartupInput;
ULONG_PTR kGdiplusToken;

Eurocat::SystemContainer systemContainer;

void __declspec(dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	systemContainer.Startup();
	*ppPlugInInstance = &systemContainer.GetPlugin();

	Gdiplus::GdiplusStartup(&kGdiplusToken, &kGdiplusStartupInput, NULL);
}

void __declspec(dllexport) EuroScopePlugInExit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	systemContainer.Cleanup();

	Gdiplus::GdiplusShutdown(kGdiplusToken);
}
