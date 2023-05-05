#pragma once

#include "warning/CheckableRadarTarget.h"

namespace Eurocat::Warning
{
	class ICheckableDataProvider
	{
	public:
		virtual ~ICheckableDataProvider() = default;
		virtual std::vector<CheckableRadarTarget> GetRadarTargets() = 0;
	};
}