#pragma once

#include "system/SystemService.h"

namespace Eurocat::Warning
{
	class WarningService : public System::SystemService
	{
	public:
		WarningService();
		void OnStart() override;
		void OnStop() override;
	};
}
