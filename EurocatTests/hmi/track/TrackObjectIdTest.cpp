#include "pch.h"

#include "hmi/track/TrackObjectId.h"

using ::testing::Return;

namespace Eurocat::Hmi::Track
{
	TEST(TrackObjectIdTest, Generates)
	{
		EXPECT_STREQ(TrackObjectId::Generate("MY_ID", "MY_SUFFIX"), "MY_ID:MY_SUFFIX");
	}

	TEST(TrackObjectIdTest, Extracts)
	{
		auto extraction = TrackObjectId::Extract("MY_ID:MY_SUFFIX");

		EXPECT_STREQ(extraction.trackProfileId, "MY_ID");
		EXPECT_STREQ(extraction.suffix, "MY_SUFFIX");
	}
}
