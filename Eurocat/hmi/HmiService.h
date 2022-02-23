#pragma once

#include "system/SystemService.h"

#include "hmi/unit/UnitDisplayManager.h"
#include "hmi/OptionButton.h"
#include "track/TrackManager.h"

namespace Eurocat::Hmi
{
	class HmiService : public System::SystemService
	{
	public:
		HmiService();
		void OnStart() override;
		void OnStop() override;
		void OnClickOptionButton();
		Unit::UnitDisplayManager& GetUnitDisplayManager();

	private:
		Unit::UnitDisplayManager unitDisplayManager;
		std::shared_ptr<Track::TrackManager> trackManager;
		std::shared_ptr<OptionButton> optionButton;
	};
}
