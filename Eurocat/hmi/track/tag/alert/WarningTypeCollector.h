#pragma once

#include "base/pch.h"

#include "hmi/track/tag/alert/WarningType.h"

namespace Eurocat::Hmi::Track
{
	class WarningTypeCollector
	{
	public:
		static std::vector<WarningType> GetWarningTypes(CString targetId);
	};
}