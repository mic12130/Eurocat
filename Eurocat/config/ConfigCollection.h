#pragma once

#include "config/SettingsData.h"

namespace Eurocat::Config
{
	struct ConfigCollection
	{
	public:
		ConfigCollection(SettingsData& settings) : settings(settings)
		{
		}
		
		const SettingsData settings;
	};
}