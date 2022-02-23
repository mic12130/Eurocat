#include "pch.h"

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
#include "../MockRadarTargetDataProvider.h"
#include "../MockFlightPlanDataProvider.h"

using namespace Eurocat::Hmi::Track;
using namespace Eurocat::Hmi::Unit;
using ::testing::Return;

namespace Eurocat::Hmi::Track
{
	namespace
	{
		template<typename T, typename U>
		bool IsInstanceOfType(const std::shared_ptr<U> ptr) {
			return dynamic_cast<T*>(ptr.get()) != nullptr;
		}
	}

	class TagLabelFactoryTest : public ::testing::Test
	{
	protected:
		MockRadarTargetDataProvider rt;
		MockFlightPlanDataProvider fp;
		TagAlertData alertData = TagAlertData(std::nullopt, std::nullopt);

		UnitDisplayMode unit = UnitDisplayMode::Imperial;
		IdentDisplayMode rtIdent = IdentDisplayMode::Ssr;
		IdentDisplayMode fpIdent = IdentDisplayMode::Acid;
	};

	TEST_F(TagLabelFactoryTest, ProducesLimitedTagLabels)
	{
		auto result = TagLabelFactory().GetLimitedTagLabels(
			rt, alertData, unit, rtIdent,
			false
		);

		ASSERT_EQ(result.size(), 3);

		ASSERT_EQ(result[0].size(), 3);
		EXPECT_TRUE(IsInstanceOfType<UnitIndicator2>(result[0][0]));
		EXPECT_TRUE(IsInstanceOfType<EmergencyAlertLabel>(result[0][1]));
		EXPECT_TRUE(IsInstanceOfType<WarningAlertLabel>(result[0][2]));

		ASSERT_EQ(result[1].size(), 1);
		EXPECT_TRUE(IsInstanceOfType<UncoupledIdentLabel>(result[1][0]));

		ASSERT_EQ(result[2].size(), 3);
		EXPECT_TRUE(IsInstanceOfType<LevelLabel>(result[2][0]));
		EXPECT_TRUE(IsInstanceOfType<SpaceLabel>(result[2][1]));
		EXPECT_TRUE(IsInstanceOfType<GroundSpeedLabel>(result[2][2]));
	}

	TEST_F(TagLabelFactoryTest, ProducesNormalTagLabels)
	{
		auto result = TagLabelFactory().GetTagLabelsForCoupledTrack(
			rt, fp, alertData, unit, rtIdent,
			false, false, false
		);

		ASSERT_EQ(result.size(), 4);

		ASSERT_EQ(result[0].size(), 4);
		EXPECT_TRUE(IsInstanceOfType<UnitIndicator1>(result[0][0]));
		EXPECT_TRUE(IsInstanceOfType<RunwayLabel>(result[0][1]));
		EXPECT_TRUE(IsInstanceOfType<EmergencyAlertLabel>(result[0][2]));
		EXPECT_TRUE(IsInstanceOfType<WarningAlertLabel>(result[0][3]));

		ASSERT_EQ(result[1].size(), 4);
		EXPECT_TRUE(IsInstanceOfType<UnitIndicator2>(result[1][0]));
		EXPECT_TRUE(IsInstanceOfType<IdentLabel>(result[1][1]));
		EXPECT_TRUE(IsInstanceOfType<SpaceLabel>(result[1][2]));
		EXPECT_TRUE(IsInstanceOfType<WtcLabel>(result[1][3]));

		ASSERT_EQ(result[2].size(), 6);
		EXPECT_TRUE(IsInstanceOfType<LevelLabel>(result[2][0]));
		EXPECT_TRUE(IsInstanceOfType<VsIndicatorLabel>(result[2][1]));
		EXPECT_TRUE(IsInstanceOfType<CflLabel>(result[2][2]));
		EXPECT_TRUE(IsInstanceOfType<FlightRuleIndicator>(result[2][3]));
		EXPECT_TRUE(IsInstanceOfType<GroundSpeedLabel>(result[2][4]));
		EXPECT_TRUE(IsInstanceOfType<AccIndicatorLabel>(result[2][5]));

		ASSERT_EQ(result[3].size(), 1);
		EXPECT_TRUE(IsInstanceOfType<LabelDataLabel>(result[3][0]));
	}

	TEST_F(TagLabelFactoryTest, HasAnExtraLineWhenExtended)
	{
		auto result = TagLabelFactory().GetTagLabelsForCoupledTrack(
			rt, fp, alertData, unit, rtIdent,
			false, true, false
		);

		ASSERT_EQ(result.size(), 5);
		ASSERT_EQ(result[3].size(), 3);
		EXPECT_TRUE(IsInstanceOfType<DestLabel>(result[3][0]));
		EXPECT_TRUE(IsInstanceOfType<SpaceLabel>(result[3][1]));
		EXPECT_TRUE(IsInstanceOfType<AircraftTypeLabel>(result[3][2]));
	}

	TEST_F(TagLabelFactoryTest, LabelsChangedWhenShared)
	{
		auto result = TagLabelFactory().GetTagLabelsForCoupledTrack(
			rt, fp, alertData, unit, rtIdent,
			false, true, true
		);

		ASSERT_EQ(result.size(), 5);
		ASSERT_EQ(result[3].size(), 1);
		EXPECT_TRUE(IsInstanceOfType<WaypointLabel>(result[3][0]));
	}

	TEST_F(TagLabelFactoryTest, UsesFallbackLabelsForFlightPlanTrack)
	{
		auto result = TagLabelFactory().GetTagLabelsForFlightPlanTrack(
			fp, alertData, unit, fpIdent,
			false, false
		);

		ASSERT_EQ(result.size(), 4);

		ASSERT_EQ(result[1].size(), 4);
		EXPECT_TRUE(IsInstanceOfType<UnitIndicator2>(result[1][0]));
		EXPECT_TRUE(IsInstanceOfType<FlightPlanIdentLabel>(result[1][1]));
		EXPECT_TRUE(IsInstanceOfType<SpaceLabel>(result[1][2]));
		EXPECT_TRUE(IsInstanceOfType<WtcLabel>(result[1][3]));

		ASSERT_EQ(result[2].size(), 5);
		EXPECT_TRUE(IsInstanceOfType<LevelFallbackLabel>(result[2][0]));
		EXPECT_TRUE(IsInstanceOfType<SpaceLabel>(result[2][1]));
		EXPECT_TRUE(IsInstanceOfType<CflLabel>(result[2][2]));
		EXPECT_TRUE(IsInstanceOfType<FlightRuleIndicator>(result[2][3]));
		EXPECT_TRUE(IsInstanceOfType<GroundSpeedFallbackLabel>(result[2][4]));
	}
}
