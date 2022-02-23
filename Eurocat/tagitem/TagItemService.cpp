#include "base/pch.h"

#include "tagitem/TagItemService.h"

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
	TagItemService::TagItemService(Hmi::Unit::UnitDisplayManager& unitDisplayManager)
		: unitDisplayManager(unitDisplayManager)
	{
	}

	void TagItemService::OnStart()
	{
		auto acidTagItem = std::make_shared<AcidTagItem>();
		RegisterTagItem(acidTagItem, PluginTagItemId::kAcidTagItemId, "ACID");

		auto opDataTagItem = std::make_shared<OpDataTagItem>();
		RegisterTagItem(opDataTagItem, PluginTagItemId::kOpDataTagItemId, "OP DATA");

		auto opDataFunction = std::make_shared<OpDataFunction>();
		RegisterFunction(opDataFunction, PluginFunctionId::kModifyOpDataFunctionId, "Edit OP DATA");

		auto cflTagItem = std::make_shared<CflTagItem>(unitDisplayManager);
		RegisterTagItem(cflTagItem, PluginTagItemId::kCflTagItemId, "CFL");

		auto cflFunction = std::make_shared<CflFunction>(unitDisplayManager);
		RegisterFunction(cflFunction, PluginFunctionId::kCflPopupFunctionId, "Open CFL popup");

		auto rflTagItem = std::make_shared<RflTagItem>(unitDisplayManager);
		RegisterTagItem(rflTagItem, PluginTagItemId::kRflTagItemId, "RFL");

		auto rflInIcaoFormatTagItem = std::make_shared<RflInIcaoFormatTagItem>();
		RegisterTagItem(rflInIcaoFormatTagItem, PluginTagItemId::kRflInIcaoFormatTagItemId, "RFL (ICAO field 15b format)");

		auto rflFunction = std::make_shared<RflFunction>(unitDisplayManager);
		RegisterFunction(rflFunction, PluginFunctionId::kRflPopupFunctionId, "Open RFL popup");
	}

	void TagItemService::RegisterTagItem(std::shared_ptr<Plugin::ITagItemProvider> p, int id, CString name)
	{
		PluginEventManager::Shared().AddTagItemProvider(p, id);
		PluginEnvironment::Shared().GetPlugin().RegisterTagItemType(name, id);
	}

	void TagItemService::RegisterFunction(std::shared_ptr<Plugin::IFunctionHandler> p, int id, CString name)
	{
		PluginEventManager::Shared().AddFunctionHandler(p, id);
		PluginEnvironment::Shared().GetPlugin().RegisterTagItemFunction(name, id);
	}
}
