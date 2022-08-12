#include "base/pch.h"

#include "hmi/HmiManager.h"
#include "hmi/OptionDialog.h"
#include "plugin/PluginEventManager.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi
{
	HmiManager::HmiManager()
	{
		trackManager = std::make_shared<TrackManager>(unitDisplayManager);
		optionButton = std::make_shared<OptionButton>();
		optionButton->SetClickCallback(std::bind(&HmiManager::OnClickOptionButton, this));
	}

	HmiManager::~HmiManager()
	{
		optionButton->SetClickCallback(nullptr);
	}

	void HmiManager::SubscribeToPluginEvents(Plugin::PluginEventManager& manager)
	{
		manager.AddScreenEventHandler(trackManager);
		manager.AddScreenEventHandler(optionButton);
	}

	void HmiManager::OnClickOptionButton()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())

		OptionDialog(
			unitDisplayManager,
			trackManager->GetTrackProfileManager(),
			trackManager->GetOption()
		).DoModal();
	}

	Unit::UnitDisplayManager& HmiManager::GetUnitDisplayManager()
	{
		return unitDisplayManager;
	}
}
