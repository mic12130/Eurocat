#pragma once

#include "hmi/track/tag/render_data/ITagDataProvider.h"
#include "hmi/track/tag/render_data/ExtendedLabelCalc.h"
#include "hmi/track/tag/render_data/SharedLabelCalc.h"
#include "hmi/track/tag/render_data/IdentDisplayModeCalc.h"
#include "hmi/track/tag/TagLabelFactory.h"
#include "hmi/track/IFlightPlanDataProvider.h"
#include "hmi/track/profile/TrackProfile.h"
#include "hmi/track/option/OptionData.h"
#include "hmi/unit/UnitDisplayMode.h"

namespace Eurocat::Hmi::Track
{
	class FlightPlanTrackTagData : public ITagDataProvider
	{
	public:
		FlightPlanTrackTagData(
			IFlightPlanDataProvider& fp,
			const TrackProfile& profile,
			const OptionData& option,
			Hmi::Unit::UnitDisplayMode unit)
			: fp(fp),
			profile(profile),
			option(option),
			unit(unit)
		{
		}

		TagLabelCollection GetLabels() override
		{
			auto alertData = GetAlertData();

			return TagLabelFactory().GetTagLabelsForFlightPlanTrack(
				fp, alertData,
				unit,
				IdentDisplayModeCalc::GetIdentDisplayModeForFlightPlanTrack(option),
				ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile),
				SharedLabelCalc::RendersSharedLabel(option)
			);
		}

		TagAlertData GetAlertData() override
		{
			return TagAlertData(std::nullopt, std::nullopt);
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
			return fp.GetFlightPlanTrackPosition();
		}

		bool CanOverrideFilter() override
		{
			return true;
		}

	private:
		IFlightPlanDataProvider& fp;
		const TrackProfile& profile;
		const OptionData& option;
		Hmi::Unit::UnitDisplayMode unit;
	};
}
