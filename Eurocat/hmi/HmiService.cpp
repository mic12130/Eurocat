#include "base/pch.h"

#include "hmi/HmiService.h"

#include "hmi/OptionDialog.h"
#include "plugin/PluginEventManager.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi
{
	HmiService::HmiService()
	{
		trackManager = std::make_shared<TrackManager>(unitDisplayManager);
		optionButton = std::make_shared<OptionButton>();
	}

	void HmiService::OnStart()
	{
		Plugin::PluginEventManager::Shared().AddScreenEventHandler(trackManager);
		Plugin::PluginEventManager::Shared().AddScreenEventHandler(optionButton);
		optionButton->SetClickCallback(std::bind(&HmiService::OnClickOptionButton, this));
	}

	void HmiService::OnStop()
	{
		optionButton->SetClickCallback(nullptr);
	}

	void HmiService::OnClickOptionButton()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())

		OptionDialog(
			unitDisplayManager,
			trackManager->GetTrackProfileManager(),
			trackManager->GetOption()
		).DoModal();
	}

	Unit::UnitDisplayManager& HmiService::GetUnitDisplayManager()
	{
		return unitDisplayManager;
	}
}
