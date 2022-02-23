#include "pch.h"

#include "common/unit/SpeedFormatter.h"

using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Common::Unit
{
	class SpeedFormatterTest : public ::testing::Test
	{
	protected:
	};

	TEST_F(SpeedFormatterTest, FormatsZeroKnot)
	{
		SpeedFormatter formatter(UnitDisplayMode::Imperial);
		EXPECT_STREQ(formatter.StringFromSpeed(0), "00");
	}

	TEST_F(SpeedFormatterTest, FormatsZeroKph)
	{
		SpeedFormatter formatter(UnitDisplayMode::Metric);
		EXPECT_STREQ(formatter.StringFromSpeed(0), "000");
	}

	TEST_F(SpeedFormatterTest, FormatsRegularKnot)
	{
		SpeedFormatter formatter(UnitDisplayMode::Imperial);
		EXPECT_STREQ(formatter.StringFromSpeed(1), "00");
		EXPECT_STREQ(formatter.StringFromSpeed(5), "00");
		EXPECT_STREQ(formatter.StringFromSpeed(50), "05");
		EXPECT_STREQ(formatter.StringFromSpeed(500), "50");
		EXPECT_STREQ(formatter.StringFromSpeed(999), "99");
	}

	TEST_F(SpeedFormatterTest, FormatsRegularKph)
	{
		SpeedFormatter formatter(UnitDisplayMode::Metric);
		EXPECT_STREQ(formatter.StringFromSpeed(1), "000");
		EXPECT_STREQ(formatter.StringFromSpeed(5), "000");
		EXPECT_STREQ(formatter.StringFromSpeed(50), "005");
		EXPECT_STREQ(formatter.StringFromSpeed(500), "050");
		EXPECT_STREQ(formatter.StringFromSpeed(5000), "500");
		EXPECT_STREQ(formatter.StringFromSpeed(9999), "999");
	}

	TEST_F(SpeedFormatterTest, FormatsIllegalKnot)
	{
		SpeedFormatter formatter(UnitDisplayMode::Imperial);
		EXPECT_STREQ(formatter.StringFromSpeed(-1), "00");
		EXPECT_STREQ(formatter.StringFromSpeed(1000), "99");
	}

	TEST_F(SpeedFormatterTest, FormatsIllegalKph)
	{
		SpeedFormatter formatter(UnitDisplayMode::Metric);
		EXPECT_STREQ(formatter.StringFromSpeed(-1), "000");
		EXPECT_STREQ(formatter.StringFromSpeed(10000), "999");
	}
}
