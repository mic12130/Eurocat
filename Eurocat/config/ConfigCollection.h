#pragma once

#include "config/SettingsData.h"

namespace Eurocat::Config
{
	struct ConfigCollection
	{
	public:
		ConfigCollection(SettingsData& settingsData) : settingsData(settingsData)
		{
		}

	private:
		const SettingsData settingsData;
	};
}