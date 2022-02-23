#pragma once

#include "base/pch.h"

#include "hmi/track/FlashHelper.h"
#include "hmi/track/option/OptionData.h"

namespace Eurocat::Hmi::Track
{
	class SharedLabelCalc
	{
	public:
		// Checks if shared label should be rendered for a coupled or flight plan track
		static bool RendersSharedLabel(const OptionData& option, std::shared_ptr<IFlashHelper> flashHelper = FlashHelper::ForSharedLabel())
		{
			return option.enableSharedLabel && flashHelper->ShouldRender();
		}
	};
}
