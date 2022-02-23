#include "pch.h"

#include "hmi/track/tag/render_data/IdentDisplayModeCalc.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	TEST(IdentDisplayModeCalcTest, PassesSsrDisplayModeForUncoupledTrack)
	{
		OptionData option;
		option.identDisplayMode = IdentDisplayMode::Ssr;

		auto result = IdentDisplayModeCalc::GetIdentDisplayModeForUncoupledTrack(option);

		EXPECT_EQ(result, IdentDisplayMode::Ssr);
	}

	TEST(IdentDisplayModeCalcTest, PassesTargetIdDisplayModeForUncoupledTrack)
	{
		OptionData option;
		option.identDisplayMode = IdentDisplayMode::TargetId;

		auto result = IdentDisplayModeCalc::GetIdentDisplayModeForUncoupledTrack(option);

		EXPECT_EQ(result, IdentDisplayMode::TargetId);
	}

	TEST(IdentDisplayModeCalcTest, ConvertsAcidDisplayModeForUncoupledTrack)
	{
		OptionData option;
		option.identDisplayMode = IdentDisplayMode::Acid;

		auto result = IdentDisplayModeCalc::GetIdentDisplayModeForUncoupledTrack(option);

		EXPECT_EQ(result, IdentDisplayMode::Ssr);
	}

	TEST(IdentDisplayModeCalcTest, PassesAcidDisplayModeForFlightPlanTrack)
	{
		OptionData option;
		option.identDisplayMode = IdentDisplayMode::Acid;

		auto result = IdentDisplayModeCalc::GetIdentDisplayModeForFlightPlanTrack(option);

		EXPECT_EQ(result, IdentDisplayMode::Acid);
	}

	TEST(IdentDisplayModeCalcTest, ConvertsSsrDisplayModeForFlightPlanTrack)
	{
		OptionData option;
		option.identDisplayMode = IdentDisplayMode::Ssr;

		auto result = IdentDisplayModeCalc::GetIdentDisplayModeForFlightPlanTrack(option);

		EXPECT_EQ(result, IdentDisplayMode::Acid);
	}

	TEST(IdentDisplayModeCalcTest, ConvertsTargetIdDisplayModeForFlightPlanTrack)
	{
		OptionData option;
		option.identDisplayMode = IdentDisplayMode::TargetId;

		auto result = IdentDisplayModeCalc::GetIdentDisplayModeForFlightPlanTrack(option);

		EXPECT_EQ(result, IdentDisplayMode::Acid);
	}
}
