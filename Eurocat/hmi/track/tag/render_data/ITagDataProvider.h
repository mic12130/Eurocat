#pragma once

#include "base/pch.h"

#include "hmi/track/tag/TagLabelCollection.h"
#include "hmi/track/tag/alert/TagAlertData.h"
#include "common/Coordinate.h"

namespace Eurocat::Hmi::Track
{
	class ITagDataProvider
	{
	public:
		virtual ~ITagDataProvider() = default;
		virtual TagLabelCollection GetLabels() = 0;
		virtual TagAlertData GetAlertData() = 0;
		virtual bool GetIsFlashing() = 0;
		virtual bool GetIsRepositioning() = 0;
		virtual CString GetProfileId() = 0;
		virtual std::tuple<int, int> GetOffset() = 0;
		virtual Common::Coordinate GetPosition() = 0;
		virtual bool CanOverrideFilter() = 0;
	};
}
