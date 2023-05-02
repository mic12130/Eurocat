#include "base/pch.h"

#include "external/CallsignLookup.h"

namespace Eurocat::External
{
	std::shared_ptr<CallsignLookup> CallsignLookup::shared = std::make_shared<CallsignLookup>();

	CallsignLookup& CallsignLookup::Shared()
	{
		return *shared;
	}

	std::optional<CString> CallsignLookup::GetCallsign(CString acid)
	{
		if (auto callsign = GetCallsignFromMap(acid, cachedMap); callsign.has_value())
		{
			return callsign;
		}
		else if (auto callsign = GetCallsignFromMap(acid, fullMap); callsign.has_value())
		{
			cachedMap[acid.Left(3)] = *callsign;
			return callsign;
		}

		return std::nullopt;
	}

	void CallsignLookup::SetCallsignMap(std::map<CString, CString>& map)
	{
		cachedMap.clear();
		fullMap = map;
	}

	std::optional<CString> CallsignLookup::GetCallsignFromMap(CString acid, std::map<CString, CString>& map)
	{
		auto it = map.find(acid.Left(3));

		if (it == map.end())
		{
			return std::nullopt;
		}

		return std::make_optional<CString>(it->second);
	}
}