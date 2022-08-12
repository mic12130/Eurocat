#pragma once

#include "hmi/unit/UnitDisplayManager.h"
#include "hmi/OptionButton.h"
#include "track/TrackManager.h"

namespace Eurocat::Plugin
{
	class PluginEventManager;
}

namespace Eurocat::Hmi
{
	class HmiManager
	{
	public:
		HmiManager();
		~HmiManager();
		void SubscribeToPluginEvents(Plugin::PluginEventManager& manager);
		void OnClickOptionButton();

		// Expose for tag item module
		Unit::UnitDisplayManager& GetUnitDisplayManager();

	private:
		Unit::UnitDisplayManager unitDisplayManager;
		std::shared_ptr<Track::TrackManager> trackManager;
		std::shared_ptr<OptionButton> optionButton;
	};
}
