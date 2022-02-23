#include "pch.h"

#include "hmi/track/tag/render_data/SharedLabelCalc.h"

#include "../MockFlashHelper.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	TEST(SharedLabelCalcTest, NonSharedByDefault)
	{
		OptionData option;
		option.enableSharedLabel = false;

		EXPECT_FALSE(SharedLabelCalc::RendersSharedLabel(option, std::make_shared<MockFlashHelper>(true)));
		EXPECT_FALSE(SharedLabelCalc::RendersSharedLabel(option, std::make_shared<MockFlashHelper>(false)));
	}

	TEST(SharedLabelCalcTest, SharedWhenGloballySetAndFlashingToOn)
	{
		OptionData option;
		option.enableSharedLabel = true;

		EXPECT_TRUE(SharedLabelCalc::RendersSharedLabel(option, std::make_shared<MockFlashHelper>(true)));
	}

	TEST(SharedLabelCalcTest, SharedWhenGloballySetAndFlashingToOff)
	{
		OptionData option;
		option.enableSharedLabel = true;

		EXPECT_FALSE(SharedLabelCalc::RendersSharedLabel(option, std::make_shared<MockFlashHelper>(false)));
	}
}
