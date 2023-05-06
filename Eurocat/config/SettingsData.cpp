#include "base/pch.h"

#include "config/SettingsData.h"

#include "config/SettingItemKey.h"

namespace Eurocat::Config
{
	SettingsData::SettingsData(const SettingsStorage& storage)
	{
		Loader loader(storage);

		coreGndTfcSpeedThreshold = loader.Load<int>(
			kCoreGndTfcSpeedThresholdKey, 30,
			std::make_unique<IntegerRangeValidator>(0, 100));
		coreOpDataLeadingChar = loader.Load<CString>(kCoreOpDataLeadingCharKey, "/");

		extCallsignFilePath = loader.Load<CString>(kExtCallsignFilePathKey, "");
	}
}