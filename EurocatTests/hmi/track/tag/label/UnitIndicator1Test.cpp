#include "pch.h"

#include "hmi/track/tag/label/UnitIndicator1.h"
#include "hmi/track/tag/label_content/StringContent.h"

#include "../../MockFlightPlanDataProvider.h"

using ::testing::Return;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Hmi::Track
{
	TEST(UnitIndicator1Test, UdmIsImperialAndRflIsInFeet)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetRfl)
			.WillRepeatedly(Return(35000));

		std::shared_ptr<StringContent> content =
			std::static_pointer_cast<StringContent>(UnitIndicator1(fp, UnitDisplayMode::Imperial).GetTagLabelContent());

		EXPECT_STREQ(content->string, L" ");
	}

	TEST(UnitIndicator1Test, UdmIsMetricAndRflIsInMeter)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetRfl)
			.WillRepeatedly(Return(35100));

		std::shared_ptr<StringContent> content =
			std::static_pointer_cast<StringContent>(UnitIndicator1(fp, UnitDisplayMode::Metric).GetTagLabelContent());

		EXPECT_STREQ(content->string, L" ");
	}

	TEST(UnitIndicator1Test, UdmIsImperialAndRflIsInMeter)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetRfl)
			.WillRepeatedly(Return(35100));

		std::shared_ptr<StringContent> content =
			std::static_pointer_cast<StringContent>(UnitIndicator1(fp, UnitDisplayMode::Imperial).GetTagLabelContent());

		EXPECT_STREQ(content->string, L"#");
	}

	TEST(UnitIndicator1Test, UdmIsMetricAndRflIsInFeet)
	{
		MockFlightPlanDataProvider fp;
		EXPECT_CALL(fp, GetRfl)
			.WillRepeatedly(Return(35000));

		std::shared_ptr<StringContent> content =
			std::static_pointer_cast<StringContent>(UnitIndicator1(fp, UnitDisplayMode::Metric).GetTagLabelContent());

		EXPECT_STREQ(content->string, L"#");
	}
}
