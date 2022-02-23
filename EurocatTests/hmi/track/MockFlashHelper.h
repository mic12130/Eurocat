#pragma once

#include "pch.h"

#include "hmi/track/IFlashHelper.h"

namespace Eurocat::Hmi::Track
{
	class MockFlashHelper : public IFlashHelper
	{
	public:
		MockFlashHelper(bool shouldRender = false) : shouldRender(shouldRender)
		{
			
		}

		bool ShouldRender() override
		{
			return shouldRender;
		}

		bool shouldRender;
	};
}
