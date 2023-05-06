#include "base/pch.h"

#include "config/SettingsStorage.h"

#include "config/SettingItemKey.h"
#include "helper/StringHelper.h"

namespace Eurocat::Config
{
	SettingsStorage::SettingsStorage()
	{
		AddRecognizedKeys();
	}

	void SettingsStorage::Load(std::string path)
	{
		valueMap.clear();

		if (std::filesystem::exists(std::filesystem::path(path)) == false)
		{
			spdlog::info("Skipped loading setting items because file not exist at \"{}\"", path);
			return;
		}

		spdlog::info("Start loading setting items from file \"{}\"", path);

		std::ifstream file(path);
		std::string line;

		while (std::getline(file, line))
		{
			auto tokens = StringHelper::GetComponents(line.c_str(), ':');

			if (tokens.size() != 2) { continue; }

			if (std::find(recognizedKeys.begin(), recognizedKeys.end(), tokens[0]) == recognizedKeys.end())
			{
				spdlog::warn("Ignored unknown setting item \"{}\"", tokens[0]);
			}
			else
			{
				valueMap[tokens[0]] = tokens[1];
			}
		}

		spdlog::info("Finished loading setting items (count: {})", valueMap.size());
	}

	void SettingsStorage::AddRecognizedKeys()
	{
		recognizedKeys = {
			kCoreGndTfcSpeedThresholdKey,
			kCoreOpDataLeadingCharKey,
			kExtCallsignFilePathKey
		};
	}
}