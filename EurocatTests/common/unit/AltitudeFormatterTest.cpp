#include "pch.h"

#include "common/unit/AltitudeFormatter.h"

using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Common::Unit
{
	class AltitudeFormatterTest : public ::testing::Test
	{
	protected:
	};

	TEST_F(AltitudeFormatterTest, FormatsZeroFeet)
	{
		AltitudeFormatter formatter(UnitDisplayMode::Imperial);
		EXPECT_STREQ(formatter.StringFromAltitude(0), "000");
	}

	TEST_F(AltitudeFormatterTest, FormatsZeroMeter)
	{
		AltitudeFormatter formatter(UnitDisplayMode::Metric);
		EXPECT_STREQ(formatter.StringFromAltitude(0), "0000");
	}

	TEST_F(AltitudeFormatterTest, FormatsRegularFeets)
	{
		AltitudeFormatter formatter(UnitDisplayMode::Imperial);
		EXPECT_STREQ(formatter.StringFromAltitude(1), "000");
		EXPECT_STREQ(formatter.StringFromAltitude(300), "003");
		EXPECT_STREQ(formatter.StringFromAltitude(3000), "030");
		EXPECT_STREQ(formatter.StringFromAltitude(30000), "300");
		EXPECT_STREQ(formatter.StringFromAltitude(99999), "999");
	}

	TEST_F(AltitudeFormatterTest, FormatsRegularMeters)
	{
		AltitudeFormatter formatter(UnitDisplayMode::Metric);
		EXPECT_STREQ(formatter.StringFromAltitude(1), "0000");
		EXPECT_STREQ(formatter.StringFromAltitude(60), "0006");
		EXPECT_STREQ(formatter.StringFromAltitude(600), "0060");
		EXPECT_STREQ(formatter.StringFromAltitude(6000), "0600");
		EXPECT_STREQ(formatter.StringFromAltitude(12500), "1250");
		EXPECT_STREQ(formatter.StringFromAltitude(99999), "9999");
	}

	TEST_F(AltitudeFormatterTest, FormatsIllegalFeets)
	{
		AltitudeFormatter formatter(UnitDisplayMode::Imperial);
		EXPECT_STREQ(formatter.StringFromAltitude(-1), "000");
		EXPECT_STREQ(formatter.StringFromAltitude(100000), "999");
	}

	TEST_F(AltitudeFormatterTest, FormatsIllegalMeters)
	{
		AltitudeFormatter formatter(UnitDisplayMode::Metric);
		EXPECT_STREQ(formatter.StringFromAltitude(-1), "0000");
		EXPECT_STREQ(formatter.StringFromAltitude(100000), "9999");
	}
}
