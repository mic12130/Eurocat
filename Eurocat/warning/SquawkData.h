#pragma once

#include "base/pch.h"

namespace Eurocat::Warning
{
	struct SquawkData
	{
		CString targetId;
		CString squawk;

		SquawkData(CString targetId, CString squawk)
			: targetId(targetId), squawk(squawk)
		{
		}
	};
}
