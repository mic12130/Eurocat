#include "base/pch.h"

#include "plugin/extension/OpData.h"

#include "plugin/extension/OpDataConverter.h"

namespace Eurocat::Plugin
{
	CString OpData::GetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp)
	{
		return OpDataConverter::FromEsFormat(fp.GetControllerAssignedData().GetScratchPadString());
	}

	void OpData::SetForFlightPlan(const EuroScopePlugIn::CFlightPlan& fp, CString content)
	{
		fp.GetControllerAssignedData().SetScratchPadString(OpDataConverter::ToEsFormat(content));
	}
}
