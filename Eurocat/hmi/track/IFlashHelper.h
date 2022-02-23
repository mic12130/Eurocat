#pragma once

namespace Eurocat::Hmi::Track
{
	class IFlashHelper
	{
	public:
		virtual ~IFlashHelper() = default;
		virtual bool ShouldRender() = 0;
	};
}
