#pragma once

#include "system/SystemService.h"
#include "plugin/PluginEventManager.h"
#include "plugin/PluginEnvironment.h"
#include "hmi/unit/UnitDisplayManager.h"

namespace Eurocat::TagItem
{
	// Ports Eurocat data and operations to EuroScope tag items
	class TagItemService : public System::SystemService
	{
	public:
		TagItemService(Hmi::Unit::UnitDisplayManager& unitDisplayManager);
		void OnStart() override;

	private:
		void RegisterTagItem(std::shared_ptr<Plugin::ITagItemProvider> p, int id, CString name);
		void RegisterFunction(std::shared_ptr<Plugin::IFunctionHandler> p, int id, CString name);

		Hmi::Unit::UnitDisplayManager& unitDisplayManager;
	};
}
