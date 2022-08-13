#include "base/pch.h"

#include "plugin/extension/FlightPlanProcessor.h"

#include "plugin/extension/OpData.h"

namespace Eurocat::Plugin
{
	FlightPlanProcessor::FlightPlanProcessor(EurocatPlugin& plugin) : plugin(plugin)
	{
	}

	void FlightPlanProcessor::OnTimedEvent(int counter)
	{
		for (auto fp = plugin.FlightPlanSelectFirst(); fp.IsValid(); fp = plugin.FlightPlanSelectNext(fp))
		{
		}
	}
}
