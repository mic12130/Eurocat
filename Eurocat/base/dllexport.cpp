#include "base/pch.h"

#include "plugin/PluginApp.h"

Eurocat::EurocatPluginApp kPluginApp;

Gdiplus::GdiplusStartupInput kGdiplusStartupInput;
ULONG_PTR kGdiplusToken;

void __declspec(dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	kPluginApp.Startup();
	*ppPlugInInstance = kPluginApp.GetPlugin();

	Gdiplus::GdiplusStartup(&kGdiplusToken, &kGdiplusStartupInput, NULL);
}

void __declspec(dllexport) EuroScopePlugInExit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	kPluginApp.Cleanup();

	Gdiplus::GdiplusShutdown(kGdiplusToken);
}
