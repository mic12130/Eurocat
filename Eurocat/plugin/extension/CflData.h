#pragma once

namespace Eurocat::Plugin
{
	class CflData
	{
	public:
		static std::optional<int> GetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp);
		static int SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, std::optional<int> level);
		static int SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, int level);
		static int SetNoneForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp);

	private:
		// After ES-defined reseved CFL 1 and 2, we assume 3 as NONE
		static const int kNoneCflValue = 3;
	};
}
