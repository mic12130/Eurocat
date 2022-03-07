#include "pch.h"

#include "hmi/track/symbol/SymbolRenderController.h"

#include "hmi/track/TrackColor.h"
#include "MockSymbolRenderer.h"
#include "../MockFlashHelper.h"
#include "../MockRadarTargetDataProvider.h"
#include "../MockFlightPlanDataProvider.h"
#include "../../screen/TestScreenWrapper.h"
#include "../../screen/TestGraphics.h"

using ::testing::Return;
using ::testing::_;
using namespace Eurocat::Screen;
using namespace Eurocat::Hmi::Track;
using namespace Eurocat::Common;

namespace Gdiplus
{
	bool operator==(const Gdiplus::Color& a, const Gdiplus::Color& b)
	{
		return a.GetValue() == b.GetValue();
	}
}

namespace Eurocat::Hmi::Track
{
	class SymbolRenderControllerTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			// Default state
			EXPECT_CALL(rt, IsModeI)
				.WillRepeatedly(Return(false));
			option.hidePsrSymbol = false;

			// Will not have any influence on test results
			// Just to silence the "returning default value" warning from gMock
			EXPECT_CALL(fp, GetFlightPlanTrackPosition)
				.WillRepeatedly(Return(Coordinate()));
			EXPECT_CALL(rt, GetPosition)
				.WillRepeatedly(Return(Coordinate()));
		}

		SymbolRenderController MakeController()
		{
			return SymbolRenderController(renderer, flashHelper);
		}

		MockFlightPlanDataProvider fp;
		MockRadarTargetDataProvider rt;
		OptionData option;
		Gdiplus::Color color = Gdiplus::Color::Blue;
		const SymbolObjectInfo symbolObjectInfo = SymbolObjectInfo("", "");
		TestScreenWrapper screen;
		TestGraphics graphics;
		std::shared_ptr<MockSymbolRenderer> renderer = std::make_shared<MockSymbolRenderer>();
		std::shared_ptr<MockFlashHelper> flashHelper = std::make_shared<MockFlashHelper>();
	};

	TEST_F(SymbolRenderControllerTest, RendersForSsrTrackByDefault)
	{
		EXPECT_CALL(*renderer, RenderSsrSymbol)
			.Times(1);
		EXPECT_CALL(*renderer, RenderPsrSymbol)
			.Times(1);
		EXPECT_CALL(*renderer, RenderSelectedSymbol)
			.Times(0);
		EXPECT_CALL(*renderer, AddScreenObject)
			.Times(1);

		MakeController().OnRenderSsrTrack(rt, color, option, false, symbolObjectInfo);
	}

	TEST_F(SymbolRenderControllerTest, CanRenderSelectedSymbolForSsrTrack)
	{
		EXPECT_CALL(*renderer, RenderSelectedSymbol)
			.Times(1);

		MakeController().OnRenderSsrTrack(rt, color, option, true, symbolObjectInfo);
	}

	TEST_F(SymbolRenderControllerTest, SsrSymbolInCyanWhenIdentAndFlashingToOn)
	{
		EXPECT_CALL(rt, IsModeI)
			.WillRepeatedly(Return(true));
		flashHelper->shouldRender = true;

		// Except for SSR symbol, all symbols should be still in general color
		EXPECT_CALL(*renderer, RenderSsrSymbol(_, TrackColor::kCyan))
			.Times(1);
		EXPECT_CALL(*renderer, RenderPsrSymbol(_, color))
			.Times(1);
		EXPECT_CALL(*renderer, RenderSelectedSymbol(_, color))
			.Times(1);

		MakeController().OnRenderSsrTrack(rt, color, option, true, symbolObjectInfo);
	}

	TEST_F(SymbolRenderControllerTest, SsrSymbolInGeneralColorWhenIdentAndFlashingToOff)
	{
		EXPECT_CALL(rt, IsModeI)
			.WillRepeatedly(Return(true));
		flashHelper->shouldRender = false;

		EXPECT_CALL(*renderer, RenderSsrSymbol(_, color))
			.Times(1);
		EXPECT_CALL(*renderer, RenderPsrSymbol(_, color))
			.Times(1);
		EXPECT_CALL(*renderer, RenderSelectedSymbol(_, color))
			.Times(1);

		MakeController().OnRenderSsrTrack(rt, color, option, true, symbolObjectInfo);
	}

	TEST_F(SymbolRenderControllerTest, CanHidePsrSymbolForSsrTrack)
	{
		option.hidePsrSymbol = true;
		EXPECT_CALL(*renderer, RenderPsrSymbol)
			.Times(0);

		MakeController().OnRenderSsrTrack(rt, color, option, true, symbolObjectInfo);
	}

	TEST_F(SymbolRenderControllerTest, RendersForPsrTrack)
	{
		EXPECT_CALL(*renderer, RenderPsrSymbol)
			.Times(1);
		EXPECT_CALL(*renderer, AddScreenObject)
			.Times(1);

		MakeController().OnRenderPsrTrack(rt, color, option, symbolObjectInfo);
	}

	TEST_F(SymbolRenderControllerTest, RendersForGroundTrack)
	{
		EXPECT_CALL(*renderer, RenderGroundTrackSymbol)
			.Times(1);
		EXPECT_CALL(*renderer, AddScreenObject)
			.Times(1);

		MakeController().OnRenderGroundTrack(rt, color, symbolObjectInfo);
	}

	TEST_F(SymbolRenderControllerTest, RendersForFlightPlanTrack)
	{
		EXPECT_CALL(*renderer, RenderFlightPlanTrackSymbol)
			.Times(1);
		EXPECT_CALL(*renderer, RenderSelectedSymbol)
			.Times(0);
		EXPECT_CALL(*renderer, AddScreenObject)
			.Times(1);

		MakeController().OnRenderFlightPlanTrack(fp, color, false, symbolObjectInfo);
	}

	TEST_F(SymbolRenderControllerTest, CanRenderSelectedSymbolForFlightPlanTrack)
	{
		EXPECT_CALL(*renderer, RenderSelectedSymbol)
			.Times(1);

		MakeController().OnRenderFlightPlanTrack(fp, color, true, symbolObjectInfo);
	}
}
