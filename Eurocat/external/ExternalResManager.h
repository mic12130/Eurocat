#pragma once

#include "config/ConfigEventManager.h"

namespace Eurocat::External
{
	class ExternalResManager
		: public Config::IConfigEventHandler,
		public std::enable_shared_from_this<ExternalResManager>
	{
	public:
		void SubscribeToConfigEvents(
			Config::ConfigCollection& config,
			Config::ConfigEventManager& manager);
		void OnConfigUpdate(Config::ConfigCollection& config) override;

	private:
		void UpdateCallsignLookup(Config::ConfigCollection& config);
	};
}