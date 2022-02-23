#include "pch.h"

#include "hmi/track/tag/label/CflLabel.h"

#include "../../MockFlightPlanDataProvider.h"
#include "StringContentUtil.h"

using ::testing::Return;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Hmi::Track
{
	TEST(CflLabelTest, LevelsInFeet)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetCfl)
			.Times(1)
			.WillOnce(Return(12000));

		auto label = std::make_shared<CflLabel>(fp, UnitDisplayMode::Imperial);

		EXPECT_STREQ(GetStringContent(label)->string, L"120");
	}

	TEST(CflLabelTest, LevelsInMeter)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetCfl)
			.Times(1)
			.WillOnce(Return(13780));

		auto label = std::make_shared<CflLabel>(fp, UnitDisplayMode::Metric);

		EXPECT_STREQ(GetStringContent(label)->string, L"0420"); // 4200 meters = 13780 feets
	}

	TEST(CflLabelTest, HighlightsWhenCflNotAcknowledged)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, IsCflAcknowledged)
			.Times(1)
			.WillOnce(Return(false));

		auto label = std::make_shared<CflLabel>(fp, UnitDisplayMode::Imperial);

		auto content = GetStringContent(label);
		ASSERT_TRUE(content->overridenColor.has_value());
		ASSERT_EQ(content->overridenColor.value().GetValue(), Gdiplus::Color::White);
	}

	TEST(CflLabelTest, DoesNotHighlightWhenCflAcknowledged)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, IsCflAcknowledged)
			.Times(1)
			.WillOnce(Return(true));

		auto label = std::make_shared<CflLabel>(fp, UnitDisplayMode::Imperial);

		EXPECT_FALSE(GetStringContent(label)->overridenColor.has_value());
	}
}
