#pragma once

#include "hmi/unit/UnitDisplayManager.h"

namespace Eurocat::Plugin
{
	class PluginEventManager;
}

namespace Eurocat::TagItem
{
	// Ports Eurocat data and operations to EuroScope tag items
	class TagItemManager
	{
	public:
		TagItemManager(Hmi::Unit::UnitDisplayManager& unitDisplayManager);
		void SubscribeToPluginEvents(Plugin::PluginEventManager& manager);
		void RegisterItems(EuroScopePlugIn::CPlugIn& plugin);

	private:
		Hmi::Unit::UnitDisplayManager& unitDisplayManager;
	};
}
