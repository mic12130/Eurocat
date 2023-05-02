#pragma once

#include "config/IConfigEventHandler.h"

namespace Eurocat::Config
{
	class ConfigEventManager
	{
	public:
		ConfigEventManager(std::vector<std::shared_ptr<IConfigEventHandler>>& handlers);
		void AddConfigEventHandler(std::shared_ptr<IConfigEventHandler> handler);

	private:
		std::vector<std::shared_ptr<IConfigEventHandler>>& handlers;
	};
}