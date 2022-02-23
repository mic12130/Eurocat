#include "pch.h"

#include "common/unit/SpeedConverter.h"

namespace Eurocat::Common::Unit
{
	class SpeedConverterTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			// Equation: Kph = knots * 1.852 + 0.5
			speeds = {
				{ 296, 160 },
				{ 315, 170 },
				{ 370, 200 },
				{ 426, 230 },
				{ 463, 250 },
				{ 519, 280 }
			};
		}

		int GetKph(int i)
		{
			return std::get<0>(speeds[i]);
		}

		int GetKnots(int i)
		{
			return std::get<1>(speeds[i]);
		}

	private:
		std::vector<std::tuple<int, int>> speeds;
	};

	TEST_F(SpeedConverterTest, ZeroKphToKnot)
	{
		EXPECT_EQ(SpeedConverter::KphToKnot(0), 0);
	}

	TEST_F(SpeedConverterTest, ZeroKnotToKph)
	{
		EXPECT_EQ(SpeedConverter::KnotToKph(0), 0);
	}

	TEST_F(SpeedConverterTest, KphToKnot)
	{
		EXPECT_EQ(SpeedConverter::KphToKnot(GetKph(0)), GetKnots(0));
		EXPECT_EQ(SpeedConverter::KphToKnot(GetKph(1)), GetKnots(1));
		EXPECT_EQ(SpeedConverter::KphToKnot(GetKph(2)), GetKnots(2));
		EXPECT_EQ(SpeedConverter::KphToKnot(GetKph(3)), GetKnots(3));
		EXPECT_EQ(SpeedConverter::KphToKnot(GetKph(4)), GetKnots(4));
		EXPECT_EQ(SpeedConverter::KphToKnot(GetKph(5)), GetKnots(5));
	}

	TEST_F(SpeedConverterTest, KnotToKph)
	{
		EXPECT_EQ(SpeedConverter::KnotToKph(GetKnots(0)), GetKph(0));
		EXPECT_EQ(SpeedConverter::KnotToKph(GetKnots(1)), GetKph(1));
		EXPECT_EQ(SpeedConverter::KnotToKph(GetKnots(2)), GetKph(2));
		EXPECT_EQ(SpeedConverter::KnotToKph(GetKnots(3)), GetKph(3));
		EXPECT_EQ(SpeedConverter::KnotToKph(GetKnots(4)), GetKph(4));
		EXPECT_EQ(SpeedConverter::KnotToKph(GetKnots(5)), GetKph(5));
	}
}
