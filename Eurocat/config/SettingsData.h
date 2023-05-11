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

		// Core
		SettingItem<int> coreGndTfcSpeedThreshold;
		SettingItem<CString> coreOpDataLeadingChar;

		// STCA
		SettingItem<int> stcaLowerAlt;
		SettingItem<int> sctaLowerSpeed;
		SettingItem<int> stcaLookAheadTimeAcc;
		SettingItem<double> stcaPlanarSepAcc;
		SettingItem<int> stcaAltSepLowAcc;
		SettingItem<int> stcaAltSepHighAcc;
		SettingItem<int> stcaAltSepThresholdAcc;
		SettingItem<int> stcaRvsmAltLimitAcc;
		SettingItem<int> stcaLookAheadTimeApp;
		SettingItem<double> stcaPlanarSepApp;
		SettingItem<int> stcaAltSepLowApp;
		SettingItem<int> stcaAltSepHighApp;
		SettingItem<int> stcaAltSepThresholdApp;
		SettingItem<int> stcaRvsmAltLimitApp;
		SettingItem<int> stcaPredMaxAltOvershoot;
		SettingItem<int> stcaPredRateThreshold;
		SettingItem<int> stcaPredAltDiffThreshold;
		SettingItem<int> stcaImminentTime;
		SettingItem<int> stcaWarningTime;
		SettingItem<double> stcaQualityThreshold;
		SettingItem<int> stcaCounterThreshold;
		SettingItem<double> stcaConflictPlanarSep;
		SettingItem<int> stcaSolvedCounterThreshold;

		// External
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