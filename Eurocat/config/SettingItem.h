#pragma once

#include "base/pch.h"

#include "config/SettingsStorage.h"
#include "config/SettingItemValidator.h"

namespace Eurocat::Config
{
	template <typename T>
	class SettingItem
	{
	public:
		SettingItem() : SettingItem("", T())
		{
		}

		SettingItem(
			CString key, T defaultValue,
			std::unique_ptr<ISettingItemValidator<T>> validator = nullptr)
			: key(key), value(defaultValue), defaultValue(defaultValue), validator(std::move(validator))
		{
		}

		operator T() const
		{
			return value;
		}

		T Get() const
		{
			return value;
		}

		void LoadFromSettingsStorage(const SettingsStorage& storage)
		{
			auto newValue = storage.GetValue<T>(key);

			if (!newValue.has_value())
			{
				spdlog::info("Setting item \"{}\" is set to default value \"{}\" (Value not found)", key, defaultValue);
				value = defaultValue;
				return;
			}

			auto unwrapped = newValue.value();
			CString err;

			if (validator == nullptr || validator->IsValid(unwrapped, err))
			{
				spdlog::info("Setting item \"{}\" is set to \"{}\"", key, unwrapped);
				value = unwrapped;
			}
			else
			{
				spdlog::info("Setting item \"{}\" is set to default value \"{}\" ({})", key, defaultValue, err);
				value = defaultValue;
			}
		}

	private:
		CString key;
		T value;
		T defaultValue;
		std::shared_ptr<ISettingItemValidator<T>> validator;
	};
}