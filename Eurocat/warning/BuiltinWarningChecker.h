#pragma once

#include "plugin/ITimedEventHandler.h"
#include "WarningTypes.h"

namespace Eurocat::Warning
{
	class BuiltinWarningChecker : public Plugin::ITimedEventHandler
	{
	public:
		void OnTimedEvent(int counter) override;
		std::vector<BuiltinWarning> GetWarnings();

	private:
		std::vector<BuiltinWarning> warnings;
	};
}
