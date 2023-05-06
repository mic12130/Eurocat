#pragma once

#include "config/SettingsStorage.h"
#include "config/SettingItem.h"

namespace Eurocat::Config
{
	struct SettingsData
	{
		SettingsData(const SettingsStorage& storage);
		
		// Force this struct to be constructed from the storage
		SettingsData() = delete;

		SettingItem<int> coreGndTfcSpeedThreshold;
		SettingItem<CString> coreOpDataLeadingChar;

		SettingItem<CString> extCallsignFilePath;

	private:
		class Loader
		{
		public:
			Loader(const SettingsStorage& storage) : storage(storage) { }

			template <typename T>
			SettingItem<T> Load(
				CString key, T defaultValue,
				std::unique_ptr<ISettingItemValidator<T>> validator = nullptr)
			{
				auto item = SettingItem<T>(key, defaultValue, std::move(validator));
				item.LoadFromSettingsStorage(storage);
				return item;
			}

			const SettingsStorage& storage;
		};
	};
}