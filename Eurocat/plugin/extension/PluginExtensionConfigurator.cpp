#include "base/pch.h"

#include "plugin/extension/PluginExtensionConfigurator.h"

#include "plugin/extension/OpData.h"

namespace Eurocat::Plugin
{
	void PluginExtensionConfigurator::ApplyInitConfig(Config::ConfigCollection& config)
	{
		OnConfigUpdate(config);
	}

	void PluginExtensionConfigurator::OnConfigUpdate(Config::ConfigCollection& config)
	{
		CString leadingCharStr = config.settings.coreOpDataLeadingChar;

		if (leadingCharStr != "")
		{
			OpData::configuration.leadingChar = leadingCharStr[0];
		}
	}
}