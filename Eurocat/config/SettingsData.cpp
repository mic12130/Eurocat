#include "base/pch.h"

#include "config/SettingsData.h"

#include "config/SettingItemKey.h"

namespace Eurocat::Config
{
	SettingsData::SettingsData(const SettingsStorage& storage)
	{
		Loader loader(storage);

		// Core
		coreGndTfcSpeedThreshold = loader.Load<int>(
			kCoreGndTfcSpeedThresholdKey, 30,
			std::make_unique<IntegerRangeValidator>(0, 100));
		coreOpDataLeadingChar = loader.Load<CString>(kCoreOpDataLeadingCharKey, "/");

		// STCA
		stcaLowerAlt = loader.Load<int>(
			kStcaLowerAltKey, 0,
			std::make_unique<IntegerRangeValidator>(-600, 600));
		stcaLowerSpeed = loader.Load<int>(
			kStcaLowerSpeedKey, 30,
			std::make_unique<IntegerRangeValidator>(0, 100));
		stcaLookAheadTimeAcc = loader.Load<int>(
			kStcaLookAheadTimeAccKey, 90,
			std::make_unique<IntegerRangeValidator>(60, 120));
		stcaPlanarSepAcc = loader.Load<double>(
			kStcaPlanarSepAccKey, 3,
			std::make_unique<DoubleRangeValidator>(2, 10));
		stcaAltSepLowAcc = loader.Load<int>(
			kStcaAltSepLowAccKey, 1000,
			std::make_unique<IntegerRangeValidator>(100, 2000));
		stcaAltSepHighAcc = loader.Load<int>(
			kStcaAltSepHighAccKey, 1000,
			std::make_unique<IntegerRangeValidator>(100, 2000));
		stcaAltSepThresholdAcc = loader.Load<int>(
			kStcaAltSepThresholdAccKey, 29000,
			std::make_unique<IntegerRangeValidator>(10000, 50000));
		stcaRvsmAltLimitAcc = loader.Load<int>(
			kStcaRvsmAltLimitAccKey, 41000,
			std::make_unique<IntegerRangeValidator>(10000, 50000));
		stcaLookAheadTimeApp = loader.Load<int>(
			kStcaLookAheadTimeAppKey, 90,
			std::make_unique<IntegerRangeValidator>(60, 120));
		stcaPlanarSepApp = loader.Load<double>(
			kStcaPlanarSepAppKey, 3,
			std::make_unique<DoubleRangeValidator>(2, 10));
		stcaAltSepLowApp = loader.Load<int>(
			kStcaAltSepLowAppKey, 1000,
			std::make_unique<IntegerRangeValidator>(100, 2000));
		stcaAltSepHighApp = loader.Load<int>(
			kStcaAltSepHighAppKey, 1000,
			std::make_unique<IntegerRangeValidator>(100, 2000));
		stcaAltSepThresholdApp = loader.Load<int>(
			kStcaAltSepThresholdAppKey, 29000,
			std::make_unique<IntegerRangeValidator>(10000, 50000));
		stcaRvsmAltLimitApp = loader.Load<int>(
			kStcaRvsmAltLimitAppKey, 41000,
			std::make_unique<IntegerRangeValidator>(10000, 50000));
		stcaPredMaxAltOvershoot = loader.Load<int>(
			kStcaPredMaxAltOvershootKey, 200,
			std::make_unique<IntegerRangeValidator>(0, 1000));
		stcaPredRateThreshold = loader.Load<int>(
			kStcaPredRateThresholdKey, 500,
			std::make_unique<IntegerRangeValidator>(0, 4000));
		stcaPredAltDiffThreshold = loader.Load<int>(
			kStcaPredAltDiffThresholdKey, 1000,
			std::make_unique<IntegerRangeValidator>(0, 1000));
		stcaImminentTime = loader.Load<int>(
			kStcaImminentTimeKey, 30,
			std::make_unique<IntegerRangeValidator>(0, 60));
		stcaWarningTime = loader.Load<int>(
			kStcaWarningTimeKey, 60,
			std::make_unique<IntegerRangeValidator>(30, 120));
		stcaQualityThreshold = loader.Load<double>(
			kStcaQualityThresholdKey, 0.7,
			std::make_unique<DoubleRangeValidator>(0.5, 0.9));
		stcaCounterThreshold = loader.Load<int>(
			kStcaCounterThresholdKey, 2,
			std::make_unique<IntegerRangeValidator>(1, 5));
		stcaConflictPlanarSep = loader.Load<double>(
			kStcaConflictPlanarSepKey, 3,
			std::make_unique<DoubleRangeValidator>(2, 10));
		stcaSolvedCounterThreshold = loader.Load<int>(
			kStcaSolvedCounterThresholdKey, 2,
			std::make_unique<IntegerRangeValidator>(1, 5));

		// External
		extCallsignFilePath = loader.Load<CString>(kExtCallsignFilePathKey, "");
	}
}