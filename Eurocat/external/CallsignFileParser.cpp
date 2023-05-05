#include "base/pch.h"

#include "external/CallsignFileParser.h"

#include "helper/StringHelper.h"

namespace Eurocat::External
{
	std::map<CString, CString> CallsignFileParser::Parse(std::string path)
	{
		std::map<CString, CString> result;

		if (std::filesystem::exists(std::filesystem::path(path)) == false)
		{
			spdlog::info("Skipped parsing callsign file because file not exist at \"{}\"", path);
			return { };
		}

		spdlog::info("Start parsing callsign file \"{}\"", path);

		std::ifstream file(path);
		std::string line;

		while (std::getline(file, line))
		{
			auto tokens = StringHelper::GetComponents(line.c_str(), '\t');

			if (tokens.size() == 3)
			{
				auto code = tokens[0].Trim();
				auto callsign = tokens[2].Trim();
				result[code] = callsign;
			}
		}

		spdlog::info("Finished parsing callsign file (count: {})", result.size());
		return result;
	}
}