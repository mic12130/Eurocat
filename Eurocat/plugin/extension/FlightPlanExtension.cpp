#include "base/pch.h"

#include "plugin/extension/FlightPlanExtension.h"

#include "plugin/extension/CflData.h"
#include "plugin/extension/OpData.h"
#include "plugin/extension/FlightPlanAttributeContainer.h"

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
		return FlightPlanAttributeContainer::Shared().AttributeForFlightPlan(fp).isCflAcknowledged;
	}

	void FlightPlanExtension::SetCflAcknowledged(bool val)
	{
		FlightPlanAttributeContainer::Shared().AttributeForFlightPlan(fp).isCflAcknowledged = val;
	}

	Common::FlightPlanState FlightPlanExtension::GetCurrentState()
	{
		return FlightPlanAttributeContainer::Shared().AttributeForFlightPlan(fp).currentState;
	}

	Common::FlightPlanState FlightPlanExtension::GetLastState()
	{
		return FlightPlanAttributeContainer::Shared().AttributeForFlightPlan(fp).lastState;
	}

	CTime FlightPlanExtension::GetLastStateUpdateTime()
	{
		return FlightPlanAttributeContainer::Shared().AttributeForFlightPlan(fp).lastStateUpdateTime;
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
