#pragma once

#include "hmi/track/tag/alert/EmergencyInfo.h"
#include "hmi/track/tag/alert/WarningInfo.h"
#include "hmi/track/tag/alert/BorderType.h"

namespace Eurocat::Hmi::Track
{
	class TagAlertData
	{
	public:
		TagAlertData(std::optional<EmergencyInfo> emergencyInfo, std::optional<WarningInfo> warningInfo);
		BorderType GetBorderType() const;

		const std::optional<EmergencyInfo> emergencyInfo;
		const std::optional<WarningInfo> warningInfo;
	};
}
