#include "base/pch.h"
#include "TrackProfileManager.h"

namespace Eurocat::Hmi::Track
{
	TrackProfileManager::TrackProfileManager()
	{
	}

	TrackProfile TrackProfileManager::GetOrCreateProfileForCoupledTrack(CString flightPlanId, CString radarTargetId)
	{
		return GetOrCreateProfile(TrackProfile::TrackType::Coupled, flightPlanId, radarTargetId);
	}

	TrackProfile TrackProfileManager::GetOrCreateProfileForUncoupledTrack(CString radarTargetId)
	{
		return GetOrCreateProfile(TrackProfile::TrackType::Uncoupled, std::nullopt, radarTargetId);
	}

	TrackProfile TrackProfileManager::GetOrCreateProfileForFlightPlanTrack(CString flightPlanId)
	{
		return GetOrCreateProfile(TrackProfile::TrackType::FlightPlan, flightPlanId, std::nullopt);
	}

	bool TrackProfileManager::TryGetProfile(CString identifier, TrackProfile& profile)
	{
		for (auto& tmp : profiles)
		{
			if (tmp.id == identifier)
			{
				profile = tmp;
				return true;
			}
		}

		return false;
	}

	bool TrackProfileManager::TryUpdateProfile(const TrackProfile& profile)
	{
		for (auto& tmp : profiles)
		{
			if (tmp.id == profile.id)
			{
				tmp = TrackProfile(profile);
				return true;
			}
		}

		return false;
	}

	void TrackProfileManager::ResetUserSetVel()
	{
		for (auto& tmp : profiles)
		{
			tmp.userSetVel = std::nullopt;
		}
	}

	void TrackProfileManager::ResetUserSetExtended()
	{
		for (auto& tmp : profiles)
		{
			tmp.userSetExtended = std::nullopt;
		}
	}

	TrackProfile TrackProfileManager::GetOrCreateProfile(TrackProfile::TrackType trackType, std::optional<CString> flightPlanId, std::optional<CString> radarTargetId)
	{
		TrackProfile profile;

		if (TryGetProfile(trackType, flightPlanId, radarTargetId, profile) == false)
		{
			CString idStr;
			idStr.Format("%d", nextGeneratedId);
			nextGeneratedId += 1;

			profile = TrackProfile();
			profile.id = idStr;
			profile.trackType = trackType;
			profile.flightPlanId = flightPlanId;
			profile.radarTargetId = radarTargetId;
			profiles.push_back(profile);
		}

		return profile;
	}

	bool TrackProfileManager::TryGetProfile(TrackProfile::TrackType trackType, std::optional<CString> flightPlanId, std::optional<CString> radarTargetId, TrackProfile& profile)
	{
		for (auto& tmp : profiles)
		{
			if (tmp.trackType == trackType &&
				tmp.flightPlanId == flightPlanId &&
				tmp.radarTargetId == radarTargetId)
			{
				profile = tmp;
				return true;
			}
		}

		return false;
	}
}
