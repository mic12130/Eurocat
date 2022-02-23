#include "base/pch.h"

#include "common/OpData.h"

#include "common/OpDataConverter.h"

namespace Eurocat::Common
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
