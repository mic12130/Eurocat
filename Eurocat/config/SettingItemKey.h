#pragma once

#include "base/pch.h"

namespace Eurocat::Config
{
	// Core
	const CString kCoreGndTfcSpeedThresholdKey = "Core_GndTfcSpeedThreshold";
	const CString kCoreOpDataLeadingCharKey = "Core_OpDataLeadingChar";

	// STCA
	const CString kStcaLowerAltKey = "STCA_LowerAlt";
	const CString kStcaLowerSpeedKey = "STCA_LowerSpeed";
	const CString kStcaLookAheadTimeAccKey = "STCA_LookAheadTimeAcc";
	const CString kStcaPlanarSepAccKey = "STCA_PlanarSepAcc";
	const CString kStcaAltSepLowAccKey = "STCA_AltSepLowAcc";
	const CString kStcaAltSepHighAccKey = "STCA_AltSepHighAcc";
	const CString kStcaAltSepThresholdAccKey = "STCA_AltSepThresholdAcc";
	const CString kStcaRvsmAltLimitAccKey = "STCA_RvsmAltLimitAcc";
	const CString kStcaLookAheadTimeAppKey = "STCA_LookAheadTimeApp";
	const CString kStcaPlanarSepAppKey = "STCA_PlanarSepApp";
	const CString kStcaAltSepLowAppKey = "STCA_AltSepLowApp";
	const CString kStcaAltSepHighAppKey = "STCA_AltSepHighApp";
	const CString kStcaAltSepThresholdAppKey = "STCA_AltSepThresholdApp";
	const CString kStcaRvsmAltLimitAppKey = "STCA_RvsmAltLimitApp";
	const CString kStcaPredMaxAltOvershootKey = "STCA_PredMaxAltOvershoot";
	const CString kStcaPredRateThresholdKey = "STCA_PredRateThreshold";
	const CString kStcaPredAltDiffThresholdKey = "STCA_PredAltDiffThreshold";
	const CString kStcaImminentTimeKey = "STCA_ImminentTime";
	const CString kStcaWarningTimeKey = "STCA_WarningTime";
	const CString kStcaQualityThresholdKey = "STCA_QualityThreshold";
	const CString kStcaCounterThresholdKey = "STCA_CounterThreshold";
	const CString kStcaConflictPlanarSepKey = "STCA_ConflictPlanarSep";
	const CString kStcaSolvedCounterThresholdKey = "STCA_SolvedCounterThreshold";

	// External
	const CString kExtCallsignFilePathKey = "Ext_CallsignFilePath";
}