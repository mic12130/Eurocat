#pragma once

#include "base/pch.h"

#include "hmi/track/tag/alert/WarningType.h"
#include "hmi/track/tag/alert/WarningSelector.h"
#include "warning/RadarTargetWarningInfo.h"

namespace Eurocat::Hmi::Track
{
	struct WarningInfo
	{
		enum class Style
		{
			Style1, // Black text with yellow background
			Style2 // Red text with red background
		};

		WarningInfo(CString code, Style style) : code(code), style(style)
		{
		}

		static std::optional<WarningInfo> Make(std::vector<WarningType> warnings, WarningSelector& warningSelector)
		{
			std::map<WarningType, WarningInfo> warningInfoMap
			{
				{WarningType::Stca, WarningInfo("ST", Style::Style2) },
				{WarningType::Daiw, WarningInfo("DA", Style::Style1) },
				{WarningType::Msaw, WarningInfo("MS", Style::Style2) },
				{WarningType::Clam, WarningInfo("CL", Style::Style1) },
				{WarningType::Ram, WarningInfo("RM", Style::Style1) },
				{WarningType::Dupe, WarningInfo("DU", Style::Style1) }
			};

			if (auto selected = warningSelector.SelectWarning(warnings); selected.has_value())
			{
				return warningInfoMap.at(selected.value());
			}

			return std::nullopt;
		}

		const CString code;
		const Style style;
	};
}
