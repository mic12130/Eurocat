#include "pch.h"

#include "hmi/track/hist/HistRenderController.h"

#include "MockHistRenderer.h"
#include "../MockRadarTargetDataProvider.h"
#include "../../screen/TestScreenWrapper.h"
#include "../../screen/TestGraphics.h"

using ::testing::Return;
using ::testing::_;
using namespace Eurocat::Screen;
using namespace Eurocat::Hmi::Track;
using namespace Eurocat::Common;

namespace Eurocat::Hmi::Track
{
	class HistRenderControllerTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			// Default state
			option.enableHistoryDotsDisplay = false;
			option.historyDotsCount = 5;

			// Will not have any influence on test results
			// Just to silence the "returning default value" warning from gMock
			EXPECT_CALL(rt, GetHistoricalPositions)
				.WillRepeatedly(Return(std::vector<Coordinate>{ }));
		}

		HistRenderController MakeController()
		{
			return HistRenderController(renderer);
		}

		MockRadarTargetDataProvider rt;
		OptionData option;
		Gdiplus::Color color = Gdiplus::Color::Blue;
		TestScreenWrapper screen;
		TestGraphics graphics;
		std::shared_ptr<MockHistRenderer> renderer = std::make_shared<MockHistRenderer>();
	};

	TEST_F(HistRenderControllerTest, DoesNotRenderIfDisabled)
	{
		EXPECT_CALL(*renderer, Render)
			.Times(0);

		MakeController().OnRenderSsrTrack(rt, option, color, screen, graphics);
	}

	TEST_F(HistRenderControllerTest, RendersIfEnabled)
	{
		option.enableHistoryDotsDisplay = true;
		option.historyDotsCount = 10;

		EXPECT_CALL(*renderer, Render)
			.Times(1);
		EXPECT_CALL(rt, GetHistoricalPositions(10))
			.Times(1);

		MakeController().OnRenderSsrTrack(rt, option, color, screen, graphics);
	}
}
