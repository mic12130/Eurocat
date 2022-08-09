#include "pch.h"

#include "hmi/track/vel/VelRenderController.h"

#include "hmi/track/profile/TrackProfile.h"
#include "MockVelRenderer.h"
#include "../MockRadarTargetDataProvider.h"
#include "../../../screen/TestScreenWrapper.h"
#include "../../../screen/TestGraphics.h"

using ::testing::Return;
using namespace Eurocat::Screen;
using namespace Eurocat::Hmi::Track;
using namespace Eurocat::Common;

namespace Eurocat::Hmi::Track
{
	class VelRenderControllerTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			// Default state
			profile.userSetVel = std::nullopt;
			option.velocityVectorMinutes = false;
			option.velocityVectorMinutes = 1;

			// Will not have any influence on test results
			// Just to silence the "returning default value" warning from gMock
			EXPECT_CALL(rt, GetHistoricalPositions)
				.WillRepeatedly(Return(std::vector<Coordinate>{ }));
		}

		VelRenderController MakeController()
		{
			return VelRenderController(renderer);
		}

		MockRadarTargetDataProvider rt;
		TrackProfile profile;
		OptionData option;
		Gdiplus::Color color = Gdiplus::Color::Blue;
		TestScreenWrapper screen;
		TestGraphics graphics;
		std::shared_ptr<MockVelRenderer> renderer = std::make_shared<MockVelRenderer>();
	};

	TEST_F(VelRenderControllerTest, DoesNotRenderByDefault)
	{
		EXPECT_CALL(*renderer, Render)
			.Times(0);

		MakeController().OnRenderSsrTrack(rt, profile, option, color, screen, graphics);
	}

	TEST_F(VelRenderControllerTest, RendersIfUserSetOn)
	{
		profile.userSetVel = std::make_optional(true);

		EXPECT_CALL(*renderer, Render)
			.Times(1);

		MakeController().OnRenderSsrTrack(rt, profile, option, color, screen, graphics);
	}

	TEST_F(VelRenderControllerTest, RendersIfGloballyOn)
	{
		option.enableVelocityVectorDisplay = true;

		EXPECT_CALL(*renderer, Render)
			.Times(1);

		MakeController().OnRenderSsrTrack(rt, profile, option, color, screen, graphics);
	}

	TEST_F(VelRenderControllerTest, UserSetOnOverridesGloballyOff)
	{
		profile.userSetVel = std::make_optional(true);
		option.enableVelocityVectorDisplay = false;

		EXPECT_CALL(*renderer, Render)
			.Times(1);

		MakeController().OnRenderSsrTrack(rt, profile, option, color, screen, graphics);
	}

	TEST_F(VelRenderControllerTest, UserSetOffOverridesGloballyOn)
	{
		profile.userSetVel = std::make_optional(false);
		option.enableVelocityVectorDisplay = true;

		EXPECT_CALL(*renderer, Render)
			.Times(0);

		MakeController().OnRenderSsrTrack(rt, profile, option, color, screen, graphics);
	}
}
