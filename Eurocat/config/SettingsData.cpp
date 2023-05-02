#include "base/pch.h"

#include "config/SettingsData.h"
#include "config/SettingItemKey.h"
#include "config/SettingItemValidator.h"

namespace Eurocat::Config
{
	SettingsData::SettingsData(const SettingsStorage& storage) : storage(storage)
	{
		groundTrafficSpeedThreshold = LoadSettingItem<int>(
			kGroundTrafficSpeedThresholdKey, 30, 
			std::make_unique<IntegerRangeValidator>(0, 100));

		callsignFilePath = LoadSettingItem<CString>(kCallsignFilePathKey, "");
	}
}