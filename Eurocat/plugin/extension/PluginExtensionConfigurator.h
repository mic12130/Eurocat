#pragma once

#include "config/IConfigEventHandler.h"

namespace Eurocat::Plugin
{
	class PluginExtensionConfigurator : public Config::IConfigEventHandler
	{
	public:
		void ApplyInitConfig(Config::ConfigCollection& config);
		void OnConfigUpdate(Config::ConfigCollection& config);
	};
}