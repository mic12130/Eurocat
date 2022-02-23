#include "pch.h"

#include "hmi/track/tag/TagRenderController.h"

#include "MockTagRenderer.h"
#include "MockTagDataProvider.h"
#include "../MockAltitudeFilter.h"
#include "../MockRadarTargetDataProvider.h"
#include "../MockFlightPlanDataProvider.h"
#include "../../screen/TestScreenWrapper.h"
#include "../../screen/TestGraphics.h"

using ::testing::Return;
using namespace Eurocat::Plugin;
using namespace Eurocat::Screen;
using namespace Eurocat::Common;

namespace Eurocat::Hmi::Track
{
	class TagRenderControllerTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			// The default state, where render controller will render contents
			EXPECT_CALL(*altitudeFilter, InRange)
				.WillRepeatedly(Return(true));
		}

		TagRenderController MakeController()
		{
			return { renderer, altitudeFilter };
		}

		MockRadarTargetDataProvider rt;
		MockTagDataProvider tagData;
		Gdiplus::Color color = Gdiplus::Color::Blue;
		TestScreenWrapper screen;
		TestGraphics graphics;
		std::shared_ptr<MockTagRenderer> renderer = std::make_shared<MockTagRenderer>();
		std::shared_ptr<MockAltitudeFilter> altitudeFilter = std::make_shared<MockAltitudeFilter>();
	};

	TEST_F(TagRenderControllerTest, RendersForCoupledTrackByDefault)
	{
		auto controller = MakeController();
		EXPECT_CALL(*renderer, RenderTagLabels)
			.Times(1);

		controller.OnRenderCoupledTrack(rt, tagData, color, screen, graphics);
	}

	TEST_F(TagRenderControllerTest, RendersForUncoupledTrackByDefault)
	{
		auto controller = MakeController();
		EXPECT_CALL(*renderer, RenderTagLabels)
			.Times(1);

		controller.OnRenderUncoupledTrack(rt, tagData, color, screen, graphics);
	}

	TEST_F(TagRenderControllerTest, RendersForFlightPlanTrackByDefault)
	{
		auto controller = MakeController();
		EXPECT_CALL(*renderer, RenderTagLabels)
			.Times(1);

		controller.OnRenderFlightPlanTrack(tagData, color, screen, graphics);
	}

	TEST_F(TagRenderControllerTest, UncoupledTrackNotInAltitudeRange)
	{
		auto controller = MakeController();
		EXPECT_CALL(*renderer, RenderTagLabels)
			.Times(0);
		EXPECT_CALL(*altitudeFilter, InRange)
			.WillRepeatedly(Return(false));

		controller.OnRenderUncoupledTrack(rt, tagData, color, screen, graphics);
	}

	TEST_F(TagRenderControllerTest, CoupledTrackNotInAltitudeRange)
	{
		auto controller = MakeController();
		EXPECT_CALL(*renderer, RenderTagLabels)
			.Times(0);
		EXPECT_CALL(*altitudeFilter, InRange)
			.WillRepeatedly(Return(false));

		controller.OnRenderCoupledTrack(rt, tagData, color, screen, graphics);
	}
}
