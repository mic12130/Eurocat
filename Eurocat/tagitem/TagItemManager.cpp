#include "base/pch.h"

#include "tagitem/TagItemManager.h"

#include "plugin/PluginEventManager.h"
#include "plugin/PluginTagItemId.h"
#include "plugin/PluginFunctionId.h"
#include "tagitem/AcidTagItem.h"
#include "tagitem/OpDataTagItem.h"
#include "tagitem/OpDataFunction.h"
#include "tagitem/CflTagItem.h"
#include "tagitem/CflFunction.h"
#include "tagitem/RflTagItem.h"
#include "tagitem/RflInIcaoFormatTagItem.h"
#include "tagitem/RflFunction.h"

using namespace Eurocat::Plugin;

namespace Eurocat::TagItem
{
	TagItemManager::TagItemManager(Hmi::Unit::UnitDisplayManager& unitDisplayManager)
		: unitDisplayManager(unitDisplayManager)
	{
	}

	void TagItemManager::SubscribeToPluginEvents(Plugin::PluginEventManager& manager)
	{
		auto acidTagItem = std::make_shared<AcidTagItem>();
		manager.AddTagItemProvider(acidTagItem, PluginTagItemId::kAcidTagItemId);

		auto opDataTagItem = std::make_shared<OpDataTagItem>();
		manager.AddTagItemProvider(opDataTagItem, PluginTagItemId::kOpDataTagItemId);

		auto cflTagItem = std::make_shared<CflTagItem>(unitDisplayManager);
		manager.AddTagItemProvider(cflTagItem, PluginTagItemId::kCflTagItemId);

		auto rflTagItem = std::make_shared<RflTagItem>(unitDisplayManager);
		manager.AddTagItemProvider(rflTagItem, PluginTagItemId::kRflTagItemId);

		auto rflInIcaoFormatTagItem = std::make_shared<RflInIcaoFormatTagItem>();
		manager.AddTagItemProvider(rflInIcaoFormatTagItem, PluginTagItemId::kRflInIcaoFormatTagItemId);

		auto opDataFunction = std::make_shared<OpDataFunction>();
		manager.AddFunctionHandler(opDataFunction, PluginFunctionId::kModifyOpDataFunctionId);

		auto cflFunction = std::make_shared<CflFunction>(unitDisplayManager);
		manager.AddFunctionHandler(cflFunction, PluginFunctionId::kCflPopupFunctionId);

		auto rflFunction = std::make_shared<RflFunction>(unitDisplayManager);
		manager.AddFunctionHandler(rflFunction, PluginFunctionId::kRflPopupFunctionId);
	}

	void TagItemManager::RegisterItems(EuroScopePlugIn::CPlugIn& plugin)
	{
		plugin.RegisterTagItemType("ACID", PluginTagItemId::kAcidTagItemId);
		plugin.RegisterTagItemType("OP DATA", PluginTagItemId::kOpDataTagItemId);
		plugin.RegisterTagItemType("CFL", PluginTagItemId::kCflTagItemId);
		plugin.RegisterTagItemType("RFL", PluginTagItemId::kRflTagItemId);
		plugin.RegisterTagItemType("RFL (ICAO field 15b format)", PluginTagItemId::kRflInIcaoFormatTagItemId);
		plugin.RegisterTagItemFunction("Edit OP DATA", PluginFunctionId::kModifyOpDataFunctionId);
		plugin.RegisterTagItemFunction("Open CFL popup", PluginFunctionId::kCflPopupFunctionId);
		plugin.RegisterTagItemFunction("Open RFL popup", PluginFunctionId::kRflPopupFunctionId);
	}
}
