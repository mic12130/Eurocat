#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin
{
	class ITimedEventHandler
	{
	public:
		virtual ~ITimedEventHandler() = default;
		virtual void OnTimedEvent(int counter) = 0;
	};
}
