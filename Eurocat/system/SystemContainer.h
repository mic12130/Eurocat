#pragma once

#include "plugin/Plugin.h"
#include "warning/WarningManager.h"
#include "hmi/HmiManager.h"
#include "tagitem/TagItemManager.h"

namespace Eurocat {
	class SystemContainer
	{
	public:
		static SystemContainer& Shared();
		
		void Startup();
		void Cleanup();

		Plugin::EurocatPlugin& GetPlugin() const;
		std::shared_ptr<Warning::WarningManager> GetWarningManager() const;

	private:
		static std::shared_ptr<SystemContainer> shared;

		SystemContainer() = default;
		void InitLogger();

		std::shared_ptr<Plugin::EurocatPlugin> plugin;
		std::shared_ptr<Warning::WarningManager> warningManager;
		std::shared_ptr<Hmi::HmiManager> hmiManager;
		std::shared_ptr<TagItem::TagItemManager> tagItemManager;
	};
}
