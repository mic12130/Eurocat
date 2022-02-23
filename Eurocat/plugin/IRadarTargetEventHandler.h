#pragma once

#include "base/pch.h"

namespace Eurocat::Plugin
{
	class IRadarTargetEventHandler
	{
	public:
		virtual ~IRadarTargetEventHandler() = default;
		virtual void OnRadarTargetPositionUpdate(EuroScopePlugIn::CRadarTarget radarTarget) = 0;
	};
}
