#include "base/pch.h"

#include "plugin/extension/OpData.h"

#include "plugin/extension/OpDataConverter.h"

namespace Eurocat::Plugin
{
	CString OpData::GetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp)
	{
		OpDataExtraction extraction;
		auto assignedData = fp.GetControllerAssignedData();
		extraction.text = assignedData.GetScratchPadString();
		extraction.assignedHeading = assignedData.GetAssignedHeading();
		extraction.assignedSpeed = assignedData.GetAssignedSpeed();
		extraction.assignedMach = assignedData.GetAssignedMach();
		extraction.dctPoint = assignedData.GetDirectToPointName();

		return OpDataConverter::FromEsFormat(extraction);
	}

	void OpData::SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, CString content)
	{
		auto extraction = OpDataConverter::ToEsFormat(content);
		auto assignedData = fp.GetControllerAssignedData();

		if (CString(assignedData.GetScratchPadString()) != extraction.text)
		{
			assignedData.SetScratchPadString(extraction.text);
		}

		if (assignedData.GetAssignedHeading() != extraction.assignedHeading)
		{
			assignedData.SetAssignedHeading(extraction.assignedHeading);
		}

		if (assignedData.GetAssignedSpeed() != extraction.assignedSpeed)
		{
			assignedData.SetAssignedSpeed(extraction.assignedSpeed);
		}

		if (assignedData.GetAssignedMach() != extraction.assignedMach)
		{
			assignedData.SetAssignedMach(extraction.assignedMach);
		}
	}
}
