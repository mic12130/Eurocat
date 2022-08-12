#include "base/pch.h"

#include "plugin/Plugin.h"

#include "base/versioninfo.h"
#include "screen/Screen.h"
#include "plugin/PluginEventManager.h"
#include "plugin/PluginFunctionId.h"
#include "plugin/extension/FlightPlanAttributeUpdater.h"
#include "plugin/extension/FlightPlanProcessor.h"
#include "plugin/input/EuroScopeInputManager.h"
#include "plugin/input/EuroScopeInputBridge.h"

using namespace Eurocat::Plugin::Input;
using namespace Eurocat::Screen;

namespace Eurocat::Plugin
{
	EurocatPlugin::EurocatPlugin()
		: CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
			kPluginName,
			kPluginVersion,
			kPluginAuthor,
			kPluginCopyright)
	{
		RegisterDisplayType(kScreenName, true, true, true, false);

		eventManager = std::make_shared<PluginEventManager>(
			flightPlanEventHandlers,
			radarEventHandlers,
			timedEventHandlers,
			tagItemProviders,
			functionHandlers,
			screenEventHandlers
			);

		auto attributeUpdater = std::make_shared<FlightPlanAttributeUpdater>(*this);
		eventManager->AddFlightPlanEventHandler(attributeUpdater);
		eventManager->AddTimedEventHandler(attributeUpdater);

		auto fpProcessor = std::make_shared<FlightPlanProcessor>(*this);
		eventManager->AddTimedEventHandler(fpProcessor);

		auto inputManager = std::make_shared<EuroScopeInputManager>(*this);
		eventManager->AddFunctionHandler(inputManager, PluginFunctionId::kSubmitInputFunctionId);
		EuroScopeInputBridge::shared->SetEuroScopeInputManager(inputManager);
	}

	EurocatPlugin::~EurocatPlugin()
	{
	}

	void EurocatPlugin::OnGetTagItem(EuroScopePlugIn::CFlightPlan FlightPlan, EuroScopePlugIn::CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int* pColorCode, COLORREF* pRGB, double* pFontSize)
	{
		if (tagItemProviders.find(ItemCode) != tagItemProviders.end())
		{
			tagItemProviders.at(ItemCode)->ProcessTagItem(FlightPlan, RadarTarget, ItemCode, sItemString, pColorCode, pRGB);
		}
	}

	void EurocatPlugin::OnFunctionCall(int FunctionId, const char* sItemString, POINT Pt, RECT Area)
	{
		if (functionHandlers.find(FunctionId) != functionHandlers.end())
		{
			functionHandlers.at(FunctionId)->OnFunctionCall(FunctionId, sItemString, Pt, Area);
		}
	}

	EuroScopePlugIn::CRadarScreen* EurocatPlugin::OnRadarScreenCreated(const char* sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated)
	{
		if (CString(sDisplayName) == kScreenName)
		{
			return new EurocatScreen(screenEventHandlers);
		}

		return nullptr;
	}

	void EurocatPlugin::OnRadarTargetPositionUpdate(EuroScopePlugIn::CRadarTarget RadarTarget)
	{
		for (const auto& handler : radarEventHandlers)
		{
			handler->OnRadarTargetPositionUpdate(RadarTarget);
		}
	}

	void EurocatPlugin::OnFlightPlanFlightPlanDataUpdate(EuroScopePlugIn::CFlightPlan FlightPlan)
	{
		for (const auto& handler : flightPlanEventHandlers)
		{
			handler->OnFlightPlanFlightPlanDataUpdate(FlightPlan);
		}
	}

	void EurocatPlugin::OnFlightPlanControllerAssignedDataUpdate(EuroScopePlugIn::CFlightPlan FlightPlan, int DataType)
	{
		for (const auto& handler : flightPlanEventHandlers)
		{
			handler->OnFlightPlanControllerAssignedDataUpdate(FlightPlan, DataType);
		}
	}

	void EurocatPlugin::OnTimer(int Counter)
	{
		for (const auto& handler : timedEventHandlers)
		{
			handler->OnTimedEvent(Counter);
		}
	}

	std::shared_ptr<PluginEventManager> EurocatPlugin::GetEventManager() const
	{
		return eventManager;
	}
}
