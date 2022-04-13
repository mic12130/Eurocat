#pragma once

#include "hmi/track/IRadarTargetDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class RadarTargetDataProvider : public IRadarTargetDataProvider
	{
	public:
		RadarTargetDataProvider(EuroScopePlugIn::CRadarTarget& rt);
		int GetGroundSpeed() override;
		int GetPressureAltitude() override;
		int GetFlightLevel() override;
		CString GetSsr() override;
		CString GetTargetId() override;
		int GetVerticalSpeed() override;
		Common::Coordinate GetPosition() override;
		std::vector<int> GetHistoricalGroundSpeeds(int preferredCount) override;
		std::vector<Common::Coordinate> GetHistoricalPositions(int preferredCount) override;
		bool IsModeI() override;
		double GetHeading() override;

	private:
		EuroScopePlugIn::CRadarTarget rt;
	};
}
