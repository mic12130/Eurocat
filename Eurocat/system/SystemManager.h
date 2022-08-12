#pragma once

#include "plugin/Plugin.h"
#include "warning/WarningManager.h"
#include "hmi/HmiManager.h"
#include "tagitem/TagItemManager.h"

namespace Eurocat {
	class SystemManager
	{
	public:
		static SystemManager& Shared();
		
		void Startup();
		void Cleanup();

		Plugin::EurocatPlugin& GetPlugin() const;
		std::shared_ptr<Warning::WarningManager> GetWarningManager() const;

	private:
		static std::shared_ptr<SystemManager> shared;

		SystemManager() = default;

		std::shared_ptr<Plugin::EurocatPlugin> plugin;
		std::shared_ptr<Warning::WarningManager> warningManager;
		std::shared_ptr<Hmi::HmiManager> hmiManager;
		std::shared_ptr<TagItem::TagItemManager> tagItemManager;
	};
}
