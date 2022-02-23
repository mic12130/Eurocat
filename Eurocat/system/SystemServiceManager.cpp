#include "base/pch.h"

#include "system/SystemServiceManager.h"

#include "warning/WarningService.h"
#include "hmi/HmiService.h"
#include "tagitem/TagItemService.h"

using namespace Eurocat::Warning;
using namespace Eurocat::Hmi;
using namespace Eurocat::TagItem;

namespace Eurocat::System
{
	void SystemServiceManager::StartPluginService(std::unique_ptr<Plugin::PluginService> service)
	{
		pluginService = std::move(service);
		pluginService->OnStart();
	}

	void SystemServiceManager::StartOtherServices()
	{
		// Warning service
		auto safetyNetsService = std::make_shared<WarningService>();
		services.push_back(safetyNetsService);

		// HMI service
		auto hmiService = std::make_shared<HmiService>();
		priorityServices.push_back(hmiService);

		// Tag item service
		auto tagItemService = std::make_shared<TagItemService>(
			hmiService->GetUnitDisplayManager()
			);
		priorityServices.push_back(tagItemService);

		// Start all
		for (const auto& service : services)
		{
			service->OnStart();
		}
		
		for (const auto& service : priorityServices)
		{
			service->OnStart();
		}
	}

	void SystemServiceManager::StopServices()
	{
		for (const auto& service : priorityServices)
		{
			service->OnStop();
		}

		priorityServices.clear();
		
		for (const auto& service : services)
		{
			service->OnStop();
		}

		services.clear();

		pluginService->OnStop();
	}
}
