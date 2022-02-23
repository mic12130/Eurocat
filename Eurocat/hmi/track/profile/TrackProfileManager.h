#pragma once

#include "hmi/track/profile/TrackProfile.h"

namespace Eurocat::Hmi::Track
{
	class TrackProfileManager
	{
	public:
		TrackProfileManager();

		TrackProfile GetOrCreateProfileForCoupledTrack(CString flightPlanId, CString radarTargetId);
		TrackProfile GetOrCreateProfileForUncoupledTrack(CString radarTargetId);
		TrackProfile GetOrCreateProfileForFlightPlanTrack(CString flightPlanId);
		bool TryGetProfile(CString identifier, TrackProfile& profile);
		bool TryUpdateProfile(const TrackProfile& profile);
		void ResetUserSetVel();
		void ResetUserSetExtended();

	private:
		TrackProfile GetOrCreateProfile(
			TrackProfile::TrackType trackType,
			std::optional<CString> flightPlanId,
			std::optional<CString> radarTargetId
		);
		bool TryGetProfile(
			TrackProfile::TrackType trackType,
			std::optional<CString> flightPlanId,
			std::optional<CString> radarTargetId,
			TrackProfile& profile
		);

		std::vector<TrackProfile> profiles;

		inline static int nextGeneratedId = 0;
	};
}
