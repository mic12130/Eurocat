#pragma once

#include "plugin/ITimedEventHandler.h"
#include "warning/DupeSquawkChecker.h"

namespace Eurocat::Warning
{
	class DupeSquawkCheckScheduler : public Plugin::ITimedEventHandler
	{
	public:
		DupeSquawkCheckScheduler(std::shared_ptr<DupeSquawkChecker> checker);
		void OnTimedEvent(int counter) override;

	private:
		std::shared_ptr<DupeSquawkChecker> checker;
	};
}
