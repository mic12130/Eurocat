#pragma once

namespace Eurocat::External
{
	class CallsignLookup
	{
	public:
		static CallsignLookup& Shared();

		CallsignLookup() = default;
		std::optional<CString> GetCallsign(CString acid);
		void SetCallsignMap(std::map<CString, CString>& map);

	private:
		static std::shared_ptr< CallsignLookup> shared;

		std::optional<CString> GetCallsignFromMap(CString acid, std::map<CString, CString>& map);
		std::map<CString, CString> fullMap;
		std::map<CString, CString> cachedMap;
	};
}