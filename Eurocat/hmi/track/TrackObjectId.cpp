#include "base/pch.h"

#include "hmi/track/TrackObjectId.h"

#include "helper/StringHelper.h"

namespace Eurocat::Hmi::Track
{
	CString TrackObjectId::Generate(CString trackProfileId, CString suffix)
	{
		if (suffix.IsEmpty())
		{
			throw std::invalid_argument("Suffix cannot be empty");
		}

		CString str;
		str.Format("%s:%s", trackProfileId.GetString(), suffix.GetString());

		return str;
	}

	TrackObjectIdExtraction TrackObjectId::Extract(CString objectId)
	{
		auto components = StringHelper::GetComponents(objectId, ':');

		if (components.size() != 2)
		{
			throw std::invalid_argument("Invalid object ID");
		}

		return { components[0], components[1] };
	}
}
