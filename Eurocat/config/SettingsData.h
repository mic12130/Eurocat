#pragma once

#include "config/SettingsStorage.h"
#include "config/SettingItem.h"

namespace Eurocat::Config
{
	struct SettingsData
	{
	public:
		SettingsData(const SettingsStorage& storage);

		int GetCoreGndTfcSpeedThreshold() const
		{
			return coreGndTfcSpeedThreshold->Get();
		}

		CString GetExtCallsignFilePath() const
		{
			return extCallsignFilePath->Get();
		}

	private:
		std::shared_ptr<SettingItem<int>> coreGndTfcSpeedThreshold;
		std::shared_ptr<SettingItem<CString>> extCallsignFilePath;

	private:
		template <typename T>
		auto LoadSettingItem(
			CString key,
			T defaultValue,
			std::unique_ptr<ISettingItemValidator<T>> validator = nullptr
		) -> std::shared_ptr<SettingItem<T>>;

		const SettingsStorage& storage;
	};

	template<typename T>
	inline auto SettingsData::LoadSettingItem(CString key, T defaultValue, std::unique_ptr<ISettingItemValidator<T>> validator) -> std::shared_ptr<SettingItem<T>>
	{
		auto item = std::make_shared<SettingItem<T>>(key, defaultValue, std::move(validator));
		item->LoadFromSettingsStorage(storage);
		return item;
	}
}