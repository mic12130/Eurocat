#pragma once

#include "hmi/track/tag/render_data/ITagDataProvider.h"
#include "hmi/track/tag/render_data/IdentDisplayModeCalc.h"
#include "hmi/track/tag/render_data/AltFilterOverrideCheck.h"
#include "hmi/track/tag/TagLabelFactory.h"
#include "hmi/track/IRadarTargetDataProvider.h"
#include "hmi/track/profile/TrackProfile.h"
#include "hmi/track/option/OptionData.h"
#include "hmi/track/tag/alert/WarningTypeCollection.h"
#include "hmi/track/tag/alert/WarningSelector.h"
#include "system/SystemContainer.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class UncoupledTrackTagData : public ITagDataProvider
	{
	public:
		UncoupledTrackTagData(
			IRadarTargetDataProvider& rt,
			const TrackProfile& profile,
			const OptionData& option,
			Hmi::Unit::UnitDisplayMode unit)
			: rt(rt),
			profile(profile),
			option(option),
			unit(unit)
		{
		}

		TagLabelCollection GetLabels() override
		{
			auto alertData = GetAlertData();

			return TagLabelFactory().GetLimitedTagLabels(
				rt, alertData,
				unit,
				IdentDisplayModeCalc::GetIdentDisplayModeForUncoupledTrack(option),
				rt.GetPressureAltitude() > SystemContainer::Shared().GetPlugin().GetTransitionAltitude()
			);
		}

		TagAlertData GetAlertData() override
		{
			// Hides all warnings except DUPE
			WarningSelector selector;
			selector.allowedWarnings = std::vector{ WarningType::Dupe };

			WarningTypeCollection warnings;
			warnings.AddFromRadarTargetWarningInfo(SystemContainer::Shared().GetWarningManager()->GetWarningInfoByTargetId(rt.GetTargetId()));

			return TagAlertData(EmergencyInfo::Make(rt.GetSsr()), WarningInfo::Make(warnings.GetWaningTypes(), selector));
		}

		bool GetIsFlashing() override
		{
			return false;
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
			return AltFilterOverrideCheck::CheckForUncoupledTrack(rt);
		}

	private:
		IRadarTargetDataProvider& rt;
		const TrackProfile& profile;
		const OptionData& option;
		Hmi::Unit::UnitDisplayMode unit;
	};
}
