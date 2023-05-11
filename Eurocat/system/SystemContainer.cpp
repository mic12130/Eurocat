#include "base/pch.h"

#include "system/SystemContainer.h"

#include "spdlog/sinks/basic_file_sink.h"

#include "helper/FilesystemHelper.h"
#include "plugin/PluginAccess.h"
#include "plugin/extension/PluginExtensionConfigurator.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Warning;
using namespace Eurocat::Hmi;
using namespace Eurocat::TagItem;
using namespace Eurocat::Config;
using namespace Eurocat::External;
namespace fs = std::filesystem;

namespace Eurocat
{
	void SystemContainer::Startup()
	{
		InitLogger();

		spdlog::info("Starting system");

		spdlog::info("Starting plugin");
		plugin = std::make_shared<EurocatPlugin>();
		PluginAccess::SetupShared(plugin);

		spdlog::info("Starting config manager");
		configManager = std::make_shared<ConfigManager>();
		configManager->Load();
		auto config = configManager->MakeConfigCollection();

		spdlog::info("Starting warning manager");
		warningManager = std::make_shared<WarningManager>();
		warningManager->SubscribeToPluginEvents(*plugin->GetEventManager());
		WarningData::SetupShared(warningManager->MakeWarningData());

		spdlog::info("Starting hmi manager");
		hmiManager = std::make_shared<HmiManager>();
		hmiManager->SubscribeToPluginEvents(*plugin->GetEventManager());

		spdlog::info("Starting tag item manager");
		tagItemManager = std::make_shared<TagItemManager>(hmiManager->GetUnitDisplayManager());
		tagItemManager->SubscribeToPluginEvents(*plugin->GetEventManager());
		tagItemManager->RegisterItems(*plugin);

		spdlog::info("Starting external resources manager");
		externalResManager = std::make_shared<ExternalResManager>();
		externalResManager->SubscribeToConfigEvents(config, configManager->GetEventManager());

		spdlog::info("Setting up plugin components");
		SetupPluginExtension(config);
	}

	void SystemContainer::Cleanup()
	{
		spdlog::info("Cleaning up");
	}

	Plugin::EurocatPlugin& SystemContainer::GetPlugin() const
	{
		return *plugin;
	}

	void SystemContainer::InitLogger()
	{
		std::string fileName = FilesystemHelper::GetDllPath() + ".log";

		try
		{
			auto logger = spdlog::basic_logger_mt("logger", fileName, true);
			spdlog::set_default_logger(logger);
		}
		catch (const spdlog::spdlog_ex&)
		{
		}
	}

	void SystemContainer::SetupPluginExtension(Config::ConfigCollection& config)
	{
		auto configurator = std::make_shared<PluginExtensionConfigurator>();
		configurator->ApplyInitConfig(config);
		configManager->GetEventManager().AddConfigEventHandler(configurator);
	}
}
