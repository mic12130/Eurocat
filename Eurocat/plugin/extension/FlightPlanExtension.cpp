#include "base/pch.h"

#include "plugin/extension/FlightPlanExtension.h"

#include "plugin/extension/CflData.h"
#include "plugin/extension/OpData.h"
#include "plugin/PluginAccess.h"

namespace Eurocat::Plugin
{
	FlightPlanExtension::FlightPlanExtension(EuroScopePlugIn::CFlightPlan& fp) : fp(fp)
	{
	}

	std::optional<int> FlightPlanExtension::GetCfl()
	{
		return CflData::GetForFlightPlan(fp);

	}

	bool FlightPlanExtension::SetCfl(std::optional<int> level)
	{
		return CflData::SetForFlightPlan(fp, level);
	}

	bool FlightPlanExtension::SetCfl(int level)
	{
		return CflData::SetForFlightPlan(fp, level);
	}

	bool FlightPlanExtension::SetNoneCfl()
	{
		return CflData::SetNoneForFlightPlan(fp);
	}

	CString FlightPlanExtension::GetOpDataText()
	{
		return OpData::GetForFlightPlan(fp);
	}

	void FlightPlanExtension::SetOpDataText(CString text)
	{
		OpData::SetForFlightPlan(fp, text);
	}

	bool FlightPlanExtension::GetCflAcknowledged()
	{
		return PluginAccess::Shared().FlightPlanAttribute(fp).isCflAcknowledged;
	}

	void FlightPlanExtension::SetCflAcknowledged(bool val)
	{
		PluginAccess::Shared().FlightPlanAttribute(fp).isCflAcknowledged = val;
	}

	Common::FlightPlanState FlightPlanExtension::GetCurrentState()
	{
		return PluginAccess::Shared().FlightPlanAttribute(fp).currentState;
	}

	Common::FlightPlanState FlightPlanExtension::GetLastState()
	{
		return PluginAccess::Shared().FlightPlanAttribute(fp).lastState;
	}

	CTime FlightPlanExtension::GetLastStateUpdateTime()
	{
		return PluginAccess::Shared().FlightPlanAttribute(fp).lastStateUpdateTime;
	}

	bool FlightPlanExtension::GetWritable()
	{
		if (fp.GetTrackingControllerIsMe() || CString(fp.GetTrackingControllerCallsign()).IsEmpty())
		{
			return true;
		}

		return false;
	}
}
