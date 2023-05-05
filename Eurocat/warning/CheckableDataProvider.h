#pragma once

#include "warning/ICheckableDataProvider.h"

namespace Eurocat::Warning
{
	class CheckableDataProvider : public ICheckableDataProvider
	{
	public:
		std::vector<CheckableRadarTarget> GetRadarTargets() override;
		void UpdateFromPlugin();

	private:
		std::vector<CheckableRadarTarget> elements;
		std::shared_mutex m;
	};
}
