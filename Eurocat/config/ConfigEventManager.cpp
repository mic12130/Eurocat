#include "base/pch.h"

#include "config/ConfigEventManager.h"

namespace Eurocat::Config
{
    ConfigEventManager::ConfigEventManager(std::vector<std::shared_ptr<IConfigEventHandler>>& handlers)
        : handlers(handlers)
    {
    }

    void ConfigEventManager::AddConfigEventHandler(std::shared_ptr<IConfigEventHandler> handler)
    {
        handlers.push_back(handler);
    }
}