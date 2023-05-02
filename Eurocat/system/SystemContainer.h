#pragma once

#include "plugin/Plugin.h"
#include "warning/WarningManager.h"
#include "hmi/HmiManager.h"
#include "tagitem/TagItemManager.h"
#include "config/ConfigManager.h"
#include "external/ExternalResManager.h"

namespace Eurocat {
	class SystemContainer
	{
	public:
		SystemContainer() = default;
		void Startup();
		void Cleanup();
		Plugin::EurocatPlugin& GetPlugin() const;

	private:
		void InitLogger();

		std::shared_ptr<Plugin::EurocatPlugin> plugin;
		std::shared_ptr<Config::ConfigManager> configManager;
		std::shared_ptr<Warning::WarningManager> warningManager;
		std::shared_ptr<Hmi::HmiManager> hmiManager;
		std::shared_ptr<TagItem::TagItemManager> tagItemManager;
		std::shared_ptr<External::ExternalResManager> externalResManager;
	};
}
