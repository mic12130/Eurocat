#include "pch.h"

#include "hmi/track/tag/label/GroundSpeedLabel.h"
#include "common/unit/SpeedConverter.h"

#include "../../MockRadarTargetDataProvider.h"
#include "StringContentUtil.h"

using ::testing::Return;
using namespace Eurocat::Hmi::Unit;
using namespace Eurocat::Common::Unit;

namespace Eurocat::Hmi::Track
{
	TEST(GroundSpeedLabelTest, WorksWithKnot)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetGroundSpeed)
			.Times(3)
			.WillOnce(Return(0))
			.WillOnce(Return(300))
			.WillOnce(Return(994));

		auto label = std::make_shared<GroundSpeedLabel>(rt, UnitDisplayMode::Imperial);

		EXPECT_STREQ(GetStringContent(label)->string, L"00");
		EXPECT_STREQ(GetStringContent(label)->string, L"30");
		EXPECT_STREQ(GetStringContent(label)->string, L"99");
	}

	TEST(GroundSpeedLabelTest, WorksWithKph)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetGroundSpeed)
			.Times(3)
			.WillOnce(Return(0))
			.WillOnce(Return(300))
			.WillOnce(Return(1076));

		auto label = std::make_shared<GroundSpeedLabel>(rt, UnitDisplayMode::Metric);

		EXPECT_STREQ(GetStringContent(label)->string, L"000");
		EXPECT_STREQ(GetStringContent(label)->string, L"055"); // 300 knots = 556 kph
		EXPECT_STREQ(GetStringContent(label)->string, L"199"); // 1076 knots = 1993 kph
	}

	TEST(GroundSpeedLabelTest, KnotTooLarge)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetGroundSpeed)
			.Times(2)
			.WillOnce(Return(995))
			.WillOnce(Return(1200));

		auto label = std::make_shared<GroundSpeedLabel>(rt, UnitDisplayMode::Imperial);

		EXPECT_STREQ(GetStringContent(label)->string, L"++");
		EXPECT_STREQ(GetStringContent(label)->string, L"++");
	}

	TEST(GroundSpeedLabelTest, KphTooLarge)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetGroundSpeed)
			.Times(2)
			.WillOnce(Return(1077))
			.WillOnce(Return(1200));

		auto label = std::make_shared<GroundSpeedLabel>(rt, UnitDisplayMode::Metric);

		// 1077 knots = 1995 kph, which is greater than the max value to be displayed in Metric UDM (1994 kph)
		EXPECT_STREQ(GetStringContent(label)->string, L"+++");
		EXPECT_STREQ(GetStringContent(label)->string, L"+++");
	}
}
