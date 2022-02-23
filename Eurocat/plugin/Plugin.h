#pragma once

#include "plugin/IFlightPlanEventHandler.h"
#include "plugin/IRadarTargetEventHandler.h"
#include "plugin/ITagItemProvider.h"
#include "plugin/IFunctionHandler.h"
#include "plugin/ITimedEventHandler.h"
#include "screen/IScreenEventHandler.h"
#include "system/SystemServiceManager.h"

namespace Eurocat::Plugin
{
	class EurocatPlugin : public EuroScopePlugIn::CPlugIn
	{
	public:
		EurocatPlugin(int compatibilityCode, CString name, CString version, CString author, CString copyright);
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

	private:
		std::vector<std::shared_ptr<IFlightPlanEventHandler>> flightPlanEventHandlers;
		std::vector<std::shared_ptr<IRadarTargetEventHandler>> radarEventHandlers;
		std::vector<std::shared_ptr<ITimedEventHandler>> timedEventHandlers;
		std::map<int, std::shared_ptr<ITagItemProvider>> tagItemProviders;
		std::map<int, std::shared_ptr<IFunctionHandler>> functionHandlers;
		std::vector<std::shared_ptr<Screen::IScreenEventHandler>> screenEventHandlers;

		System::SystemServiceManager systemServiceManager;

		const CString kScreenName = "Eurocat radar screen";
	};
}
