#pragma once

#include "base/pch.h"

namespace Eurocat::Hmi::Track
{
	struct EmergencyInfo
	{
		EmergencyInfo(CString code) : code(code) { }

		static std::optional<EmergencyInfo> Make(CString ssr)
		{
			if (ssr == "7700")
			{
				return std::make_optional<EmergencyInfo>("EMG");
			}
			if (ssr == "7600")
			{
				return std::make_optional<EmergencyInfo>("RAD");
			}
			if (ssr == "7500")
			{
				return std::make_optional<EmergencyInfo>("HIJ");
			}

			return std::nullopt;
		}

		const CString code;
	};
}
