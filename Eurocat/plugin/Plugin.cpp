#include "base/pch.h"

#include "plugin/Plugin.h"

#include "screen/Screen.h"
#include "plugin/PluginEnvironment.h"
#include "plugin/PluginEventManager.h"
#include "plugin/PluginService.h"
#include "plugin/extension/FlightPlanAttributeUpdater.h"
#include "plugin/input/EuroScopeInputManager.h"

using namespace Eurocat::Plugin::Extension;
using namespace Eurocat::Plugin::Input;
using namespace Eurocat::Screen;
using namespace Eurocat::System;

namespace Eurocat::Plugin
{
	EurocatPlugin::EurocatPlugin(int compatibilityCode, CString name, CString version, CString author, CString copyright)
		: CPlugIn(compatibilityCode, name, version, author, copyright)
	{
		auto pluginEnv = std::make_shared<PluginEnvironment>(*this);
		auto pluginEventManager = std::make_shared<PluginEventManager>(
			flightPlanEventHandlers,
			radarEventHandlers,
			timedEventHandlers,
			tagItemProviders,
			functionHandlers,
			screenEventHandlers
			);

		systemServiceManager.StartPluginService(std::make_unique<PluginService>(pluginEnv, pluginEventManager));
		systemServiceManager.StartOtherServices();

		RegisterDisplayType(kScreenName, true, true, true, false);
	}

	EurocatPlugin::~EurocatPlugin()
	{
		systemServiceManager.StopServices();
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
}
