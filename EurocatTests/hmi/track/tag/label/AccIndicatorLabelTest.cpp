#include "pch.h"

#include "hmi/track/tag/label/AccIndicatorLabel.h"

#include "../../MockRadarTargetDataProvider.h"
#include "StringContentUtil.h"

using ::testing::Return;

namespace Eurocat::Hmi::Track
{
	TEST(AccIndicatorLabelTest, IndicatorForAccelertion)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetGroundSpeed)
			.WillRepeatedly(Return(200));
		EXPECT_CALL(rt, GetHistoricalGroundSpeeds(1))
			.WillRepeatedly(Return(std::vector{ 190 }));

		auto label = std::make_shared<AccIndicatorLabel>(rt);

		EXPECT_STREQ(GetStringContent(label)->string, L"A");
	}

	TEST(AccIndicatorLabelTest, IndicatorForDecelertion)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetGroundSpeed)
			.WillRepeatedly(Return(200));
		EXPECT_CALL(rt, GetHistoricalGroundSpeeds(1))
			.WillRepeatedly(Return(std::vector{ 210 }));

		auto label = std::make_shared<AccIndicatorLabel>(rt);

		EXPECT_STREQ(GetStringContent(label)->string, L"L");
	}

	TEST(AccIndicatorLabelTest, SpeedUnchanged)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetGroundSpeed)
			.WillRepeatedly(Return(200));
		EXPECT_CALL(rt, GetHistoricalGroundSpeeds(1))
			.WillRepeatedly(Return(std::vector{ 200 }));

		auto label = std::make_shared<AccIndicatorLabel>(rt);

		EXPECT_STREQ(GetStringContent(label)->string, L" ");
	}

	TEST(AccIndicatorLabelTest, NoHistoricalGroundSpeedAvailable)
	{
		MockRadarTargetDataProvider rt;
		EXPECT_CALL(rt, GetGroundSpeed)
			.WillRepeatedly(Return(200));
		EXPECT_CALL(rt, GetHistoricalGroundSpeeds(1))
			.WillRepeatedly(Return(std::vector<int>()));

		auto label = std::make_shared<AccIndicatorLabel>(rt);

		EXPECT_STREQ(GetStringContent(label)->string, L" ");
	}
}
