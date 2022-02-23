#include "pch.h"

#include "hmi/track/tag/label/WaypointLabel.h"

#include "../../MockFlightPlanDataProvider.h"
#include "StringContentUtil.h"

using ::testing::Return;

namespace Eurocat::Hmi::Track
{
	TEST(WaypointLabelTest, HasTwoWaypointsAhead)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetWaypointsAhead(2))
			.WillRepeatedly(Return(std::vector<CString>{ "WPT1", "WPT2" }));

		auto label = std::make_shared<WaypointLabel>(fp);

		EXPECT_STREQ(GetStringContent(label)->string, L"WPT1 WPT2");
	}

	TEST(WaypointLabelTest, HasOneWaypointAhead)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetWaypointsAhead(2))
			.WillRepeatedly(Return(std::vector<CString>{ "WPT1" }));

		auto label = std::make_shared<WaypointLabel>(fp);

		EXPECT_STREQ(GetStringContent(label)->string, L"WPT1");
	}

	TEST(WaypointLabelTest, HasNoWaypointAhead)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetWaypointsAhead(2))
			.WillRepeatedly(Return(std::vector<CString>()));

		auto label = std::make_shared<WaypointLabel>(fp);

		EXPECT_STREQ(GetStringContent(label)->string, L"");
	}
}
