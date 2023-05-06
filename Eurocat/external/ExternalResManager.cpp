#include"base/pch.h"

#include "external/ExternalResManager.h"

#include "helper/FilesystemHelper.h"
#include "external/CallsignLookup.h"
#include "external/CallsignFileParser.h"

namespace Eurocat::External
{
	void ExternalResManager::SubscribeToConfigEvents(
		Config::ConfigCollection& config,
		Config::ConfigEventManager& manager)
	{
		manager.AddConfigEventHandler(shared_from_this());
		UpdateCallsignLookup(config);
	}

	void ExternalResManager::OnConfigUpdate(Config::ConfigCollection& config)
	{
		UpdateCallsignLookup(config);
	}

	void ExternalResManager::UpdateCallsignLookup(Config::ConfigCollection& config)
	{
		auto path = FilesystemHelper::GetDllDirPath();
		path.append("\\");
		path.append(config.settings.GetExtCallsignFilePath());
		auto map = CallsignFileParser::Parse(path);
		CallsignLookup::Shared().SetCallsignMap(map);
	}
}