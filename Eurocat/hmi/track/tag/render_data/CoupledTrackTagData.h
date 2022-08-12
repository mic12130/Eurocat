#pragma once

#include "hmi/track/tag/render_data/ITagDataProvider.h"
#include "hmi/track/tag/render_data/ExtendedLabelCalc.h"
#include "hmi/track/tag/render_data/SharedLabelCalc.h"
#include "hmi/track/tag/render_data/AltFilterOverrideCheck.h"
#include "hmi/track/tag/TagLabelFactory.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/profile/TrackProfile.h"
#include "hmi/track/option/OptionData.h"
#include "hmi/track/tag/alert/WarningTypeCollection.h"
#include "hmi/track/tag/alert/WarningSelector.h"
#include "system/SystemManager.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class CoupledTrackTagData : public ITagDataProvider
	{
	public:
		CoupledTrackTagData(
			IRadarTargetDataProvider& rt,
			IFlightPlanDataProvider& fp,
			const TrackProfile& profile,
			const OptionData& option,
			Hmi::Unit::UnitDisplayMode unit)
			: rt(rt),
			fp(fp),
			profile(profile),
			option(option),
			unit(unit)
		{
		}

		TagLabelCollection GetLabels() override
		{
			auto alertData = GetAlertData();

			return TagLabelFactory().GetTagLabelsForCoupledTrack(
				rt, fp, alertData,
				unit,
				option.identDisplayMode,
				rt.GetPressureAltitude() > SystemManager::Shared().GetPlugin().GetTransitionAltitude(),
				ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile),
				SharedLabelCalc::RendersSharedLabel(option)
			);
		}

		TagAlertData GetAlertData() override
		{
			WarningSelector selector;
			WarningTypeCollection warnings;
			warnings.AddFromRadarTargetWarningInfo(SystemManager::Shared().GetWarningManager()->GetWarningInfoByTargetId(rt.GetTargetId()));

			return TagAlertData(EmergencyInfo::Make(rt.GetSsr()), WarningInfo::Make(warnings.GetWaningTypes(), selector));
		}

		bool GetIsFlashing() override
		{
			return fp.IsAcceptedReminding() ||
				fp.GetDisplayState() == Hmi::FlightPlanDisplayState::HandOverIn;
		}

		bool GetIsRepositioning() override
		{
			return profile.isTagRepositioning;
		}

		CString GetProfileId() override
		{
			return profile.id;
		}

		std::tuple<int, int> GetOffset() override
		{
			return std::make_tuple(profile.tagOffsetX, profile.tagOffsetY);
		}

		Common::Coordinate GetPosition() override
		{
			return rt.GetPosition();
		}

		bool CanOverrideFilter() override
		{
			return AltFilterOverrideCheck::CheckForCoupledTrack(rt, fp);
		}

	private:
		IRadarTargetDataProvider& rt;
		IFlightPlanDataProvider& fp;
		const TrackProfile& profile;
		const OptionData& option;
		Hmi::Unit::UnitDisplayMode unit;
	};
}
