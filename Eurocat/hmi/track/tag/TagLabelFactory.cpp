#include "base/pch.h"

#include "hmi/track/tag/TagLabelFactory.h"

#include "hmi/track/tag/label/AircraftTypeLabel.h"
#include "hmi/track/tag/label/CflLabel.h"
#include "hmi/track/tag/label/DestLabel.h"
#include "hmi/track/tag/label/GroundSpeedLabel.h"
#include "hmi/track/tag/label/IdentLabel.h"
#include "hmi/track/tag/label/UncoupledIdentLabel.h"
#include "hmi/track/tag/label/FlightPlanIdentLabel.h"
#include "hmi/track/tag/label/LevelLabel.h"
#include "hmi/track/tag/label/VsIndicatorLabel.h"
#include "hmi/track/tag/label/RunwayLabel.h"
#include "hmi/track/tag/label/WaypointLabel.h"
#include "hmi/track/tag/label/WtcLabel.h"
#include "hmi/track/tag/label/SpaceLabel.h"
#include "hmi/track/tag/label/FlightRuleIndicator.h"
#include "hmi/track/tag/label/AccIndicatorLabel.h"
#include "hmi/track/tag/label/UnitIndicator1.h"
#include "hmi/track/tag/label/UnitIndicator2.h"
#include "hmi/track/tag/label/LabelDataLabel.h"
#include "hmi/track/tag/label/FlightPlanFallbackLabel.h"
#include "hmi/track/tag/label/WarningAlertLabel.h"
#include "hmi/track/tag/label/EmergencyAlertLabel.h"

using namespace Eurocat::Hmi::Track;
using namespace Eurocat::Common;

namespace Eurocat::Hmi::Track
{
	TagLabelCollection TagLabelFactory::GetLimitedTagLabels(IRadarTargetDataProvider& rt, TagAlertData& alertData, Hmi::Unit::UnitDisplayMode unit, IdentDisplayMode identDisplayMode, bool aboveTransAltitude)
	{
		TagLabelCollection collection;

		// Line 1
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[0].push_back(std::make_shared<UnitIndicator2>());
		collection[0].push_back(std::make_shared<EmergencyAlertLabel>(alertData));
		collection[0].push_back(std::make_shared<WarningAlertLabel>(alertData));

		// Line 2
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[1].push_back(std::make_shared<UncoupledIdentLabel>(rt, identDisplayMode));

		// Line 3
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[2].push_back(std::make_shared<LevelLabel>(rt, unit, aboveTransAltitude));
		collection[2].push_back(std::make_shared<SpaceLabel>());
		collection[2].push_back(std::make_shared<GroundSpeedLabel>(rt, unit));

		return collection;
	}

	TagLabelCollection TagLabelFactory::GetTagLabelsForCoupledTrack(IRadarTargetDataProvider& rt, IFlightPlanDataProvider& fp, TagAlertData& alertData, Hmi::Unit::UnitDisplayMode unit, IdentDisplayMode identDisplayMode, bool aboveTransAltitude, bool extended, bool shared)
	{
		TagLabelCollection collection;
		int lineIndex = 0;

		// Line 1
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[lineIndex].push_back(std::make_shared<UnitIndicator1>(fp, unit));
		collection[lineIndex].push_back(std::make_shared<RunwayLabel>(fp));
		collection[lineIndex].push_back(std::make_shared<EmergencyAlertLabel>(alertData));
		collection[lineIndex].push_back(std::make_shared<WarningAlertLabel>(alertData));

		// Line 2
		lineIndex += 1;
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[lineIndex].push_back(std::make_shared<UnitIndicator2>());
		collection[lineIndex].push_back(std::make_shared<IdentLabel>(fp, rt, identDisplayMode));
		collection[lineIndex].push_back(std::make_shared<SpaceLabel>());
		collection[lineIndex].push_back(std::make_shared<WtcLabel>(fp));

		// Line 3
		lineIndex += 1;
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[lineIndex].push_back(std::make_shared<LevelLabel>(rt, unit, aboveTransAltitude));
		collection[lineIndex].push_back(std::make_shared<VsIndicatorLabel>(rt));
		collection[lineIndex].push_back(std::make_shared<CflLabel>(fp, unit));
		collection[lineIndex].push_back(std::make_shared<FlightRuleIndicator>(fp));
		collection[lineIndex].push_back(std::make_shared<GroundSpeedLabel>(rt, unit));
		collection[lineIndex].push_back(std::make_shared<AccIndicatorLabel>(rt));

		// Line 4
		if (extended)
		{
			lineIndex += 1;
			collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
			if (shared)
			{
				collection[lineIndex].push_back(std::make_shared<WaypointLabel>(fp));
			}
			else
			{
				collection[lineIndex].push_back(std::make_shared<DestLabel>(fp));
				collection[lineIndex].push_back(std::make_shared<SpaceLabel>());
				collection[lineIndex].push_back(std::make_shared<AircraftTypeLabel>(fp));
			}
		}

		// Line 5 (Line 4 if not extended)
		lineIndex += 1;
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[lineIndex].push_back(std::make_shared<LabelDataLabel>(fp));

		return collection;
	}

	TagLabelCollection TagLabelFactory::GetTagLabelsForFlightPlanTrack(IFlightPlanDataProvider& fp, TagAlertData& alertData, Hmi::Unit::UnitDisplayMode unit, IdentDisplayMode identDisplayMode, bool extended, bool shared)
	{
		TagLabelCollection collection;
		int lineIndex = 0;

		// Line 1
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[lineIndex].push_back(std::make_shared<UnitIndicator1>(fp, unit));
		collection[lineIndex].push_back(std::make_shared<RunwayLabel>(fp));
		collection[lineIndex].push_back(std::make_shared<EmergencyAlertLabel>(alertData));
		collection[lineIndex].push_back(std::make_shared<WarningAlertLabel>(alertData));

		// Line 2
		lineIndex += 1;
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[lineIndex].push_back(std::make_shared<UnitIndicator2>());
		collection[lineIndex].push_back(std::make_shared<FlightPlanIdentLabel>(fp, identDisplayMode));
		collection[lineIndex].push_back(std::make_shared<SpaceLabel>());
		collection[lineIndex].push_back(std::make_shared<WtcLabel>(fp));

		// Line 3
		lineIndex += 1;
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[lineIndex].push_back(std::make_shared<LevelFallbackLabel>(unit));
		collection[lineIndex].push_back(std::make_shared<SpaceLabel>());
		collection[lineIndex].push_back(std::make_shared<CflLabel>(fp, unit));
		collection[lineIndex].push_back(std::make_shared<FlightRuleIndicator>(fp));
		collection[lineIndex].push_back(std::make_shared<GroundSpeedFallbackLabel>(unit));

		// Line 4
		if (extended)
		{
			lineIndex += 1;
			collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
			if (shared)
			{
				collection[lineIndex].push_back(std::make_shared<WaypointLabel>(fp));
			}
			else
			{
				collection[lineIndex].push_back(std::make_shared<DestLabel>(fp));
				collection[lineIndex].push_back(std::make_shared<SpaceLabel>());
				collection[lineIndex].push_back(std::make_shared<AircraftTypeLabel>(fp));
			}
		}

		// Line 5 (Line 4 if not extended)
		lineIndex += 1;
		collection.push_back(std::vector<std::shared_ptr<ITagLabel>>());
		collection[lineIndex].push_back(std::make_shared<LabelDataLabel>(fp));

		return collection;
	}
}
