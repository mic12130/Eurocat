#include "base/pch.h"

#include "hmi/track/tag/label/AircraftTypeLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	AircraftTypeLabel::AircraftTypeLabel(IFlightPlanDataProvider& data)
		: data(data)
	{
	}

	std::shared_ptr<ITagLabelContent> AircraftTypeLabel::GetTagLabelContent()
	{
		return std::make_shared<StringContent>(data.GetAircraftType());
	}
}
