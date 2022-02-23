#pragma once

#include "pch.h"

namespace Eurocat::Screen
{
	class TestScreen : public EuroScopePlugIn::CRadarScreen
	{
	public:
		virtual ~TestScreen() = default;
		void OnAsrContentToBeClosed() override
		{
		}
	};
}
