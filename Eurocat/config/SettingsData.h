#pragma once

#include "config/SettingsStorage.h"
#include "config/SettingItem.h"

namespace Eurocat::Config
{
	struct SettingsData
	{
	public:
		SettingsData(const SettingsStorage& storage);

		int GetGroundTrafficSpeedThreshold() const
		{
			return groundTrafficSpeedThreshold->Get();
		}

		CString GetCallsignFilePath() const
		{
			return callsignFilePath->Get();
		}

	private:
		template <typename T>
		auto LoadSettingItem(
			CString key,
			T defaultValue,
			std::unique_ptr<ISettingItemValidator<T>> validator = nullptr
		) -> std::shared_ptr<SettingItem<T>>;

		const SettingsStorage& storage;

		std::shared_ptr<SettingItem<int>> groundTrafficSpeedThreshold;
		std::shared_ptr<SettingItem<CString>> callsignFilePath;
	};

	template<typename T>
	inline auto SettingsData::LoadSettingItem(CString key, T defaultValue, std::unique_ptr<ISettingItemValidator<T>> validator) -> std::shared_ptr<SettingItem<T>>
	{
		auto item = std::make_shared<SettingItem<T>>(key, defaultValue, std::move(validator));
		item->LoadFromSettingsStorage(storage);
		return item;
	}
}