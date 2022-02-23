#include "pch.h"

#include "hmi/track/tag/render_data/ExtendedLabelCalc.h"

#include "../MockFlightPlanDataProvider.h"

using ::testing::Return;
using namespace Eurocat::Common;
using namespace Eurocat::Hmi;
using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	TEST(ExtendedLabelCalcTest, NonExtendedByDefault)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = false;
		profile.userSetExtended = std::nullopt;

		EXPECT_FALSE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}

	TEST(ExtendedLabelCalcTest, ExtendedIfUserSet)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = false;
		profile.userSetExtended = std::make_optional(true);

		EXPECT_TRUE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}

	TEST(ExtendedLabelCalcTest, NonExtendedIfNonConcernedEvenGloballySet)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = true;
		profile.userSetExtended = std::nullopt;
		EXPECT_CALL(fp, GetDisplayState)
			.WillRepeatedly(Return(FlightPlanDisplayState::NotConcerned));

		EXPECT_FALSE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}

	TEST(ExtendedLabelCalcTest, ExtendedIfJurisdictionWhenGloballySet)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = true;
		profile.userSetExtended = std::nullopt;
		EXPECT_CALL(fp, GetDisplayState)
			.WillRepeatedly(Return(FlightPlanDisplayState::Jurisdiction));

		EXPECT_TRUE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}

	TEST(ExtendedLabelCalcTest, ExtendedIfAnnouncedWhenGloballySet)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = true;
		profile.userSetExtended = std::nullopt;
		EXPECT_CALL(fp, GetDisplayState)
			.WillRepeatedly(Return(FlightPlanDisplayState::Announced));

		EXPECT_TRUE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}

	TEST(ExtendedLabelCalcTest, ExtendedIfHandOverInWhenGloballySet)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = true;
		profile.userSetExtended = std::nullopt;
		EXPECT_CALL(fp, GetDisplayState)
			.WillRepeatedly(Return(FlightPlanDisplayState::HandOverIn));

		EXPECT_TRUE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}

	TEST(ExtendedLabelCalcTest, ExtendedIfHandOverOutWhenGloballySet)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = true;
		profile.userSetExtended = std::nullopt;
		EXPECT_CALL(fp, GetDisplayState)
			.WillRepeatedly(Return(FlightPlanDisplayState::HandOverOut));

		EXPECT_TRUE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}

	TEST(ExtendedLabelCalcTest, UserSetExtendedOverridesGlobal)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = false;
		profile.userSetExtended = std::make_optional(true);

		EXPECT_TRUE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}

	TEST(ExtendedLabelCalcTest, UserSetNonExtendedOverridesGlobal)
	{
		OptionData option;
		TrackProfile profile;
		MockFlightPlanDataProvider fp;
		option.enableExtendedLabel = true;
		profile.userSetExtended = std::make_optional(false);
		EXPECT_CALL(fp, GetDisplayState)
			.WillRepeatedly(Return(FlightPlanDisplayState::Jurisdiction));

		EXPECT_FALSE(ExtendedLabelCalc::RendersExtendedLabel(option, fp, profile));
	}
}
