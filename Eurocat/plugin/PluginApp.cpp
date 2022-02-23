#include "base/pch.h"

#include "plugin/PluginApp.h"

#include "base/versioninfo.h"
#include "plugin/Plugin.h"

namespace Eurocat
{
	EuroScopePlugIn::CPlugIn* EurocatPluginApp::GetPlugin()
	{
		return createdPlugin.get();
	}

	void EurocatPluginApp::Startup()
	{
		createdPlugin = std::make_shared<Plugin::EurocatPlugin>(
			EuroScopePlugIn::COMPATIBILITY_CODE,
			kPluginName,
			kPluginVersion,
			kPluginAuthor,
			kPluginCopyright);
	}

	void EurocatPluginApp::Cleanup()
	{
		createdPlugin.reset();
	}
}
