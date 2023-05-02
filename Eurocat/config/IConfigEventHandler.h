#pragma once

#include "config/ConfigCollection.h"

namespace Eurocat::Config
{
	class IConfigEventHandler
	{
	public:
		virtual ~IConfigEventHandler() = default;
		virtual void OnConfigUpdate(ConfigCollection& config) = 0;
	};
}