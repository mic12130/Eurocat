#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin
{
	struct OpDataExtraction
	{
		CString text = "";
		int assignedHeading = 0;
		int assignedSpeed = 0;
		int assignedMach = 0;
		CString dctPoint = "";
	};

	inline bool operator==(const OpDataExtraction& lhs, const OpDataExtraction& rhs)
	{
		auto lhsTuple = std::tie(lhs.text, lhs.assignedHeading, lhs.assignedSpeed, lhs.assignedMach, lhs.dctPoint);
		auto rhsTuple = std::tie(rhs.text, rhs.assignedHeading, rhs.assignedSpeed, rhs.assignedMach, rhs.dctPoint);
		return lhsTuple == rhsTuple;
	}
}
