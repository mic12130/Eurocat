#include "pch.h"

#include "hmi/track/tag/label/LevelLabel.h"
#include "common/unit/AltitudeConverter.h"

#include "../../MockRadarTargetDataProvider.h"
#include "StringContentUtil.h"

using ::testing::Return;
using namespace Eurocat::Hmi::Unit;
using namespace Eurocat::Common::Unit;

namespace Eurocat::Hmi::Track
{
	TEST(LevelLabelTest, LevelsInFeet)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetPressureAltitude)
			.Times(0);
		EXPECT_CALL(rt, GetFlightLevel)
			.Times(3)
			.WillOnce(Return(0))
			.WillOnce(Return(12000))
			.WillOnce(Return(99999));

		auto label = std::make_shared<LevelLabel>(rt, UnitDisplayMode::Imperial, true);

		EXPECT_STREQ(GetStringContent(label)->string, L"000");
		EXPECT_STREQ(GetStringContent(label)->string, L"120");
		EXPECT_STREQ(GetStringContent(label)->string, L"999");
	}

	TEST(LevelLabelTest, LevelsInMeter)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetPressureAltitude)
			.Times(0);
		EXPECT_CALL(rt, GetFlightLevel)
			.Times(3)
			.WillOnce(Return(0))
			.WillOnce(Return(13780))
			.WillOnce(Return(99999));

		auto label = std::make_shared<LevelLabel>(rt, UnitDisplayMode::Metric, true);

		EXPECT_STREQ(GetStringContent(label)->string, L"0000");
		EXPECT_STREQ(GetStringContent(label)->string, L"0420"); // 4200 meters = 13780 feets
		EXPECT_STREQ(GetStringContent(label)->string, L"3048"); // 30480 meters = 99999 feets
	}

	TEST(LevelLabelTest, UnderlineVisibleWhenAboveTa)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetFlightLevel)
			.WillRepeatedly(Return(35000));

		auto label = std::make_shared<LevelLabel>(rt, UnitDisplayMode::Imperial, true);

		EXPECT_FALSE(GetStringContent(label)->hasUnderline);
	}

	TEST(LevelLabelTest, UnderlineInvisibleWhenBelowTa)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetPressureAltitude)
			.WillRepeatedly(Return(5000));

		auto label = std::make_shared<LevelLabel>(rt, UnitDisplayMode::Imperial, false);

		EXPECT_TRUE(GetStringContent(label)->hasUnderline);
	}

	// When level is below 0 or above 99999 (source input, in feets), it will considered to be "out of range"
	TEST(LevelLabelTest, LevelOutOfRange)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetPressureAltitude)
			.Times(2)
			.WillOnce(Return(-1))
			.WillOnce(Return(100000));

		auto label = std::make_shared<LevelLabel>(rt, UnitDisplayMode::Imperial, false);

		EXPECT_STREQ(GetStringContent(label)->string, L"INV");
		EXPECT_STREQ(GetStringContent(label)->string, L"INV");
	}
}
