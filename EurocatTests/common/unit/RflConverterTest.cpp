#include "pch.h"

#include "common/unit/RflConverter.h"

namespace Eurocat::Common::Unit
{
	TEST(RflConverterTest, HandlesZeroFromEs)
	{
		EXPECT_EQ(RflConverter::GetRflFromEsFormat(0).value, 0);
	}

	TEST(RflConverterTest, HandlesChineseRvsmLevelFromEs)
	{
		RflModel rfl = RflConverter::GetRflFromEsFormat(34100);
		EXPECT_EQ(rfl.value, 10400);
		EXPECT_TRUE(rfl.isMeter);
	}

	TEST(RflConverterTest, HandlesGeneralRvsmLevelFromEs)
	{
		RflModel rfl = RflConverter::GetRflFromEsFormat(34000);
		EXPECT_EQ(rfl.value, 34000);
		EXPECT_FALSE(rfl.isMeter);
	}

	TEST(RflConverterTest, HandlesRoughLevelFromEs)
	{
		RflModel rfl = RflConverter::GetRflFromEsFormat(12345);
		EXPECT_EQ(rfl.value, 12345);
		EXPECT_FALSE(rfl.isMeter);
	}

	TEST(RflConverterTest, PassesZeroToEs)
	{
		EXPECT_EQ(RflConverter::RestoreRflToEsFormat(RflModel(0, true)), 0);
		EXPECT_EQ(RflConverter::RestoreRflToEsFormat(RflModel(0, false)), 0);
	}

	TEST(RflConverterTest, PassesFeetToEs)
	{
		EXPECT_EQ(RflConverter::RestoreRflToEsFormat(RflModel(37000, false)), 37000);
	}

	TEST(RflConverterTest, PassesUnrecognizedMeterToEs)
	{
		EXPECT_EQ(RflConverter::RestoreRflToEsFormat(RflModel(11310, true)), int(11310 / 0.3048 + 0.5));
	}

	TEST(RflConverterTest, PassesRecognizedMeterToEs)
	{
		EXPECT_EQ(RflConverter::RestoreRflToEsFormat(RflModel(11300, true)), 37100);
	}
}
