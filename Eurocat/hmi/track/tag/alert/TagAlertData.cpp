#include "base/pch.h"

#include "hmi/track/tag/alert/TagAlertData.h"

namespace Eurocat::Hmi::Track
{
	TagAlertData::TagAlertData(std::optional<EmergencyInfo> emergencyInfo, std::optional<WarningInfo> warningInfo)
		: emergencyInfo(std::move(emergencyInfo)), warningInfo(std::move(warningInfo))
	{
	}

	BorderType TagAlertData::GetBorderType() const
	{
		// Considers emergency first
		if (emergencyInfo.has_value())
		{
			return BorderType::Red;
		}

		if (warningInfo.has_value())
		{
			if (warningInfo->style == WarningInfo::Style::Style1)
			{
				return BorderType::Yellow;
			}
			if (warningInfo->style == WarningInfo::Style::Style2)
			{
				return BorderType::Red;
			}
		}

		return BorderType::None;
	}
}
