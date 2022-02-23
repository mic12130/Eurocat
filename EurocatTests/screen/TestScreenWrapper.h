#pragma once

#include "TestScreen.h"
#include "screen/ScreenWrapper.h"

namespace Eurocat::Screen
{
	class TestScreenWrapper : public ScreenWrapper
	{
	public:
		TestScreenWrapper() : ScreenWrapper(testScreen)
		{
		}

	private:
		inline static TestScreen testScreen;
	};
}
