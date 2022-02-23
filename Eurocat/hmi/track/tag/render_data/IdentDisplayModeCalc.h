#pragma once

#include "base/pch.h"

#include "hmi/track/option/OptionData.h"

using namespace Eurocat::Hmi::Track;

namespace Eurocat::Hmi::Track
{
	class IdentDisplayModeCalc
	{
	public:
		static IdentDisplayMode GetIdentDisplayModeForUncoupledTrack(const OptionData& option)
		{
			// ACID is unknown for uncoupled tracks, 
			// so SSR will be displayed if ACID is selected in the GUI
			if (option.identDisplayMode == IdentDisplayMode::Acid)
			{
				return IdentDisplayMode::Ssr;
			}

			return option.identDisplayMode;
		}

		static IdentDisplayMode GetIdentDisplayModeForFlightPlanTrack(const OptionData& option)
		{
			// SSR and Target ID is unknown for flight plan tracks, 
			// so ACID will be displayed if SSR or Target ID is selected in the GUI
			if (option.identDisplayMode == IdentDisplayMode::Ssr ||
				option.identDisplayMode == IdentDisplayMode::TargetId)
			{
				return IdentDisplayMode::Acid;
			}

			return option.identDisplayMode;
		}
	};
}
