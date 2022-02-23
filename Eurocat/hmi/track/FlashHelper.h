#pragma once

#include "hmi/track/IFlashHelper.h"

namespace Eurocat::Hmi::Track
{
	class FlashHelper : public IFlashHelper
	{
	public:
		static std::shared_ptr<FlashHelper> Regular()
		{
			static auto ptr = std::make_shared<FlashHelper>();
			return ptr;
		}

		static std::shared_ptr<FlashHelper> ForSharedLabel()
		{
			static auto ptr = std::make_shared<FlashHelper>(3);
			return ptr;
		}

		FlashHelper(unsigned interval = 1);
		bool ShouldRender() override;

	private:

		unsigned interval;
	};
}
