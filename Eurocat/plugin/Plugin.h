#pragma once

#include "plugin/PluginEventManager.h"
#include "screen/IScreenEventHandler.h"

namespace Eurocat::Plugin
{
	class EurocatPlugin : public EuroScopePlugIn::CPlugIn
	{
	public:
		EurocatPlugin();
		~EurocatPlugin();

		void OnGetTagItem(
			EuroScopePlugIn::CFlightPlan FlightPlan,
			EuroScopePlugIn::CRadarTarget RadarTarget,
			int ItemCode, int TagData,
			char sItemString[16],
			int* pColorCode,
			COLORREF* pRGB,
			double* pFontSize) override;
		void OnFunctionCall(
			int FunctionId,
			const char* sItemString,
			POINT Pt,
			RECT Area) override;
		EuroScopePlugIn::CRadarScreen* OnRadarScreenCreated(
			const char* sDisplayName,
			bool NeedRadarContent,
			bool GeoReferenced, bool CanBeSaved,
			bool CanBeCreated) override;
		void OnRadarTargetPositionUpdate(EuroScopePlugIn::CRadarTarget RadarTarget) override;
		void OnFlightPlanFlightPlanDataUpdate(EuroScopePlugIn::CFlightPlan FlightPlan) override;
		void OnFlightPlanControllerAssignedDataUpdate(EuroScopePlugIn::CFlightPlan FlightPlan, int DataType) override;
		void OnTimer(int Counter) override;

		std::shared_ptr<PluginEventManager> GetEventManager() const;

	private:
		std::vector<std::shared_ptr<IFlightPlanEventHandler>> flightPlanEventHandlers;
		std::vector<std::shared_ptr<IRadarTargetEventHandler>> radarEventHandlers;
		std::vector<std::shared_ptr<ITimedEventHandler>> timedEventHandlers;
		std::map<int, std::shared_ptr<ITagItemProvider>> tagItemProviders;
		std::map<int, std::shared_ptr<IFunctionHandler>> functionHandlers;
		std::vector<std::shared_ptr<Screen::IScreenEventHandler>> screenEventHandlers;
		std::shared_ptr<PluginEventManager> eventManager;

		const CString kScreenName = "Eurocat radar screen";
	};
}
