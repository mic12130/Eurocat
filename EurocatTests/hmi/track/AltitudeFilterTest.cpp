#include "pch.h"

#include "hmi/track/AltitudeFilter.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	class AltitudeFilterTest : public ::testing::Test
	{
	protected:
		// Initially set both filters to inactivated
		void SetUp() override {
			option.altitudeFilterLow = -1;
			option.altitudeFilterHigh = -1;
		}

		OptionData option;
		AltitudeFilter filter = AltitudeFilter(option);
	};

	TEST_F(AltitudeFilterTest, BothFiltersInactivated)
	{
		EXPECT_TRUE(filter.InRange(0));
		EXPECT_TRUE(filter.InRange(100000000));
	}

	TEST_F(AltitudeFilterTest, BothFiltersActivated)
	{
		option.altitudeFilterHigh = 20000;
		option.altitudeFilterLow = 10000;

		EXPECT_FALSE(filter.InRange(25000));
		EXPECT_FALSE(filter.InRange(20001));
		EXPECT_TRUE(filter.InRange(20000));
		EXPECT_TRUE(filter.InRange(15000));
		EXPECT_TRUE(filter.InRange(10000));
		EXPECT_FALSE(filter.InRange(9999));
		EXPECT_FALSE(filter.InRange(5000));
	}

	TEST_F(AltitudeFilterTest, OnlyLowFilterActivated)
	{
		option.altitudeFilterLow = 3000;
		EXPECT_TRUE(filter.InRange(5000));
		EXPECT_TRUE(filter.InRange(3000));
		EXPECT_FALSE(filter.InRange(2999));
		EXPECT_FALSE(filter.InRange(2000));
	}

	TEST_F(AltitudeFilterTest, OnlyHighFilterActivated)
	{
		option.altitudeFilterHigh = 30000;
		EXPECT_FALSE(filter.InRange(32000));
		EXPECT_FALSE(filter.InRange(30001));
		EXPECT_TRUE(filter.InRange(30000));
		EXPECT_TRUE(filter.InRange(20000));
	}
}
