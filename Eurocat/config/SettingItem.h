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
		SettingItem(
			CString key, T defaultValue,
			std::unique_ptr<ISettingItemValidator<T>> validator = nullptr)
			: key(key), value(defaultValue), defaultValue(defaultValue), validator(std::move(validator))
		{
		}

		T& Get()
		{
			return value;
		}

		void LoadFromSettingsStorage(const SettingsStorage& storage)
		{
			auto newValue = storage.GetValue<T>(key);

			if (!newValue.has_value())
			{
				LOG(INFO) << "Setting item " << key << " is set to default value " << defaultValue << " (Value not found)";
				value = defaultValue;
				return;
			}

			auto unwrapped = newValue.value();
			CString err;

			if (validator == nullptr || validator->IsValid(unwrapped, err))
			{
				LOG(INFO) << "Setting item " << key << " is set to " << unwrapped;
				value = unwrapped;
			}
			else
			{
				LOG(INFO) << "Setting item " << key << " is set to default value " << defaultValue << " (" << err << ")";
				value = defaultValue;
			}
		}

	private:
		CString key;
		T value;
		T defaultValue;
		std::unique_ptr<ISettingItemValidator<T>> validator;
	};
}