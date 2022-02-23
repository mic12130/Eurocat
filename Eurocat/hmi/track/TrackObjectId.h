#pragma once

#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/TrackObjectIdExtraction.h"

namespace Eurocat::Hmi::Track
{
	class TrackObjectId
	{
	public:
		static CString Generate(CString trackProfileId, CString suffix);
		static TrackObjectIdExtraction Extract(CString objectId);

		inline static const CString kNoActionObjectId = "NO_ACTION";
		inline static const CString kRepositioningBackgroundObjectId = "REPOSITIONING_BACKGROUND";
	};
}
