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
			if (fp.GetTrackingControllerIsMe())
			{
				PassAssignedDataToLabelDataIfNeeded(fp);
			}
		}
	}

	void FlightPlanProcessor::PassAssignedDataToLabelDataIfNeeded(EuroScopePlugIn::CFlightPlan& fp)
	{
		auto assignedData = fp.GetControllerAssignedData();
		CString labelData = OpData::GetForFlightPlan(fp);
		bool updateNeeded = false;

		if (CString dct = assignedData.GetDirectToPointName(); dct != "")
		{
			if (assignedData.SetDirectToPointName(""))
			{
				labelData = labelData.IsEmpty() ? dct : dct + " " + labelData;
				updateNeeded = true;
			}
		}

		if (int heading = assignedData.GetAssignedHeading(); heading != 0)
		{
			if (assignedData.SetAssignedHeading(0))
			{
				CString str;
				str.Format("H%03d", heading);
				labelData = labelData.IsEmpty() ? str : str + " " + labelData;
				updateNeeded = true;
			}
		}

		if (int speed = assignedData.GetAssignedSpeed(); speed != 0)
		{
			if (assignedData.SetAssignedSpeed(0))
			{
				CString str;
				str.Format("S%03d", speed);
				labelData = labelData.IsEmpty() ? str : str + " " + labelData;
				updateNeeded = true;
			}
		}

		if (int mach = assignedData.GetAssignedMach(); mach != 0)
		{
			if (assignedData.SetAssignedMach(0))
			{
				CString str;
				str.Format("M%02d", mach);
				labelData = labelData.IsEmpty() ? str : str + " " + labelData;
				updateNeeded = true;
			}
		}

		if (int rate = assignedData.GetAssignedRate(); rate != 0)
		{
			if (assignedData.SetAssignedRate(0))
			{
				CString str;
				str.Format("R%04d", rate);
				labelData = labelData.IsEmpty() ? str : str + " " + labelData;
				updateNeeded = true;
			}
		}

		if (updateNeeded)
		{
			OpData::SetForFlightPlan(fp, labelData);
		}
	}
}
