#include "base/pch.h"

#include "system/SystemManager.h"

#include "helper/FileHelper.h"

using namespace Eurocat::Plugin;
using namespace Eurocat::Warning;
using namespace Eurocat::Hmi;
using namespace Eurocat::TagItem;
namespace fs = std::filesystem;

namespace Eurocat
{
	std::shared_ptr<SystemManager> SystemManager::shared = std::shared_ptr<SystemManager>(new SystemManager());

	SystemManager& SystemManager::Shared()
	{
		return *shared;
	}

	void SystemManager::Startup()
	{
		// In this period, do not access the shared instance of system manager,
		// because we cannot ensure the components to be accessed have been initialized

		InitLogger();

		LOG(INFO) << "Starting system";

		LOG(INFO) << "Starting plugin";
		plugin = std::make_shared<EurocatPlugin>();

		LOG(INFO) << "Starting warning manager";
		warningManager = std::make_shared<WarningManager>();
		warningManager->SubscribeToPluginEvents(*plugin->GetEventManager());

		LOG(INFO) << "Starting hmi manager";
		hmiManager = std::make_shared<HmiManager>();
		hmiManager->SubscribeToPluginEvents(*plugin->GetEventManager());

		LOG(INFO) << "Starting tag item manager";
		tagItemManager = std::make_shared<TagItemManager>(hmiManager->GetUnitDisplayManager());
		tagItemManager->SubscribeToPluginEvents(*plugin->GetEventManager());
		tagItemManager->RegisterItems(*plugin);
	}

	void SystemManager::Cleanup()
	{
		LOG(INFO) << "Cleaning up";
	}

	Plugin::EurocatPlugin& SystemManager::GetPlugin() const
	{
		return *plugin;
	}

	std::shared_ptr<WarningManager> SystemManager::GetWarningManager() const
	{
		return warningManager;
	}

	void SystemManager::InitLogger()
	{
		std::string fileName = FileHelper::GetFileName().GetString();
		fs::path fileNamePath = fileName;
		fs::path logDirPath = fileNamePath.parent_path().append("Eurocat_logs");

		if (!fs::exists(logDirPath))
		{
			fs::create_directory(logDirPath);
		}

		FLAGS_minloglevel = 0;
		FLAGS_log_dir = logDirPath.string();
		google::InitGoogleLogging(fileName.c_str());

		LOG(INFO) << "Logger initialized";
	}
}
