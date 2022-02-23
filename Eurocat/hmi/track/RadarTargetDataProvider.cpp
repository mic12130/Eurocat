#include "base/pch.h"

#include "hmi/track/RadarTargetDataProvider.h"

#include "helper/CoordinateHelper.h"

namespace Eurocat::Hmi::Track
{
	RadarTargetDataProvider::RadarTargetDataProvider(EuroScopePlugIn::CRadarTarget& rt)
		: rt(rt)
	{
	}

	int RadarTargetDataProvider::GetGroundSpeed()
	{
		return rt.GetPosition().GetReportedGS();
	}

	int RadarTargetDataProvider::GetPressureAltitude()
	{
		return rt.GetPosition().GetPressureAltitude();
	}

	int RadarTargetDataProvider::GetFlightLevel()
	{
		return rt.GetPosition().GetFlightLevel();
	}

	CString RadarTargetDataProvider::GetSsr()
	{
		return rt.GetPosition().GetSquawk();
	}

	CString RadarTargetDataProvider::GetTargetId()
	{
		return rt.GetSystemID();
	}

	int RadarTargetDataProvider::GetVerticalSpeed()
	{
		return rt.GetVerticalSpeed();
	}

	Common::Coordinate RadarTargetDataProvider::GetPosition()
	{
		return Helper::CoordinateHelper::ConvertToPosition(rt.GetPosition().GetPosition());
	}

	std::vector<int> RadarTargetDataProvider::GetHistoricalGroundSpeeds(int preferredCount)
	{
		std::vector<int> result;
		auto tempPosData = rt.GetPosition();

		for (int i = 0; i < preferredCount; i++)
		{
			tempPosData = rt.GetPreviousPosition(tempPosData);

			if (tempPosData.IsValid())
			{
				result.push_back(tempPosData.GetReportedGS());
			}
			else
			{
				break;
			}
		}

		return result;
	}

	std::vector<Common::Coordinate> RadarTargetDataProvider::GetHistoricalPositions(int preferredCount)
	{
		std::vector<Common::Coordinate> result;
		auto tempPosData = rt.GetPosition();

		for (int i = 0; i < preferredCount; i++)
		{
			tempPosData = rt.GetPreviousPosition(tempPosData);

			if (tempPosData.IsValid())
			{
				auto coord = tempPosData.GetPosition();
				result.emplace_back(coord.m_Latitude, coord.m_Longitude);
			}
			else
			{
				break;
			}
		}

		return result;
	}

	bool RadarTargetDataProvider::IsModeI()
	{
		return rt.GetPosition().GetTransponderI();
	}

	double RadarTargetDataProvider::GetHeading()
	{
		return rt.GetTrackHeading();
	}
}
