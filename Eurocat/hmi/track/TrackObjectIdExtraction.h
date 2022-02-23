#pragma once

#include "base/pch.h"

namespace Eurocat::Hmi::Track
{
	struct TrackObjectIdExtraction
	{
		TrackObjectIdExtraction(CString trackProfileId, CString suffix)
			: trackProfileId(trackProfileId), suffix(suffix)
		{
		}

		CString trackProfileId;
		CString suffix;
	};
}
