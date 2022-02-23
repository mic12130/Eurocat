#pragma once

#include "plugin/ITimedEventHandler.h"

namespace Eurocat::Warning
{
	class BuiltinWarningChecker : public Plugin::ITimedEventHandler
	{
	public:
		void OnTimedEvent(int counter) override;
		std::vector<CString> GetClamWarningTargetIds();
		std::vector<CString> GetRamWarningTargetIds();

	private:
		std::vector<CString> clamWarningTargetIds;
		std::vector<CString> ramWarningTargetIds;
	};
}
