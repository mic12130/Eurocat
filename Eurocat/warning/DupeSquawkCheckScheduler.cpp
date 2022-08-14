#include "base/pch.h"

#include "warning/DupeSquawkCheckScheduler.h"

namespace Eurocat::Warning
{
	DupeSquawkCheckScheduler::DupeSquawkCheckScheduler(std::shared_ptr<DupeSquawkChecker> checker)
		: checker(std::move(checker))
	{
	}

	void DupeSquawkCheckScheduler::OnTimedEvent(int counter)
	{
		checker->Check();
	}
}
