#pragma once

#include "config/SettingsData.h"

namespace Eurocat::Config
{
	struct ConfigCollection
	{
	public:
		ConfigCollection(const SettingsData& settings) : settings(settings)
		{
		}
		
		const SettingsData settings;
	};
}