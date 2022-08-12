#pragma once

#include "common/FlightPlanState.h"

namespace Eurocat::Plugin
{
	// Access custom flight plan data that not provided in the ES API.
	//
	// For maintainability,
	// do not access those data via separated providers (CflData, FlightPlanAttributeContainer etc),
	// use this wrapper instead.
	class FlightPlanExtension
	{
	public:
		FlightPlanExtension(EuroScopePlugIn::CFlightPlan& fp);
		std::optional<int> GetCfl();
		bool SetCfl(std::optional<int> level);
		bool SetCfl(int level);
		bool SetNoneCfl();
		CString GetOpDataText();
		void SetOpDataText(CString text);
		bool GetCflAcknowledged();
		void SetCflAcknowledged(bool val);
		Common::FlightPlanState GetCurrentState();
		Common::FlightPlanState GetLastState();
		CTime GetLastStateUpdateTime();
		bool GetWritable();

	private:
		EuroScopePlugIn::CFlightPlan& fp;
	};
}

