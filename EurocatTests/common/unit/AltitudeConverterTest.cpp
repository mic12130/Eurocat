#include "pch.h"

#include "common/unit/AltitudeConverter.h"

namespace Eurocat::Common::Unit
{
	class AltitudeConverterTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			// Equation: feets = meters / 0.3048 + 0.5
			altitudes = {
				{ 1200, 3937 },{ 4200, 13780 },
				{ 7800, 25591 }, { 9800, 32152 },
				{ 10100, 33136 }, { 12500, 41010 } };
		}

		int GetMeters(int i)
		{
			return std::get<0>(altitudes[i]);
		}

		int GetFeets(int i)
		{
			return std::get<1>(altitudes[i]);
		}

	private:
		std::vector<std::tuple<int, int>> altitudes;
	};

	TEST_F(AltitudeConverterTest, ZeroMeterToFeet)
	{
		EXPECT_EQ(AltitudeConverter::MeterToFeet(0), 0);
	}

	TEST_F(AltitudeConverterTest, ZeroFeetToMeter)
	{
		EXPECT_EQ(AltitudeConverter::FeetToMeter(0), 0);
	}

	TEST_F(AltitudeConverterTest, MetersToFeets)
	{
		EXPECT_EQ(AltitudeConverter::MeterToFeet(GetMeters(0)), GetFeets(0));
		EXPECT_EQ(AltitudeConverter::MeterToFeet(GetMeters(1)), GetFeets(1));
		EXPECT_EQ(AltitudeConverter::MeterToFeet(GetMeters(2)), GetFeets(2));
	}

	TEST_F(AltitudeConverterTest, FeetsToMeters)
	{
		EXPECT_EQ(AltitudeConverter::FeetToMeter(GetFeets(0)), GetMeters(0));
		EXPECT_EQ(AltitudeConverter::FeetToMeter(GetFeets(1)), GetMeters(1));
		EXPECT_EQ(AltitudeConverter::FeetToMeter(GetFeets(2)), GetMeters(2));
	}
}
