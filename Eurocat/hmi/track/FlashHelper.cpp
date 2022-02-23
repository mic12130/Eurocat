#include "base/pch.h"

#include "hmi/track/FlashHelper.h"

namespace Eurocat::Hmi::Track
{
	FlashHelper::FlashHelper(unsigned interval) : interval(interval)
	{
	}

	bool FlashHelper::ShouldRender()
	{
		return (CTime::GetCurrentTime().GetTime() / interval) % 2 == 0;
	}
}
