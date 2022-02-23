#pragma once

#include "plugin/PluginEnvironment.h"
#include "screen/ScreenWrapper.h"

namespace Eurocat::Hmi::Track
{
	class EuroScopeFunctionHelper
	{
		class SelectionRestorer
		{
		public:
			SelectionRestorer()
				: selectedFp(Plugin::PluginEnvironment::Shared().GetPlugin().FlightPlanSelectASEL()),
				selectedRt(Plugin::PluginEnvironment::Shared().GetPlugin().RadarTargetSelectASEL())
			{
			}

			void Restore()
			{
				EuroScopePlugIn::CPlugIn& plugin = Plugin::PluginEnvironment::Shared().GetPlugin();

				if (selectedFp.IsValid())
				{
					plugin.SetASELAircraft(selectedFp);
				}
				else if (selectedRt.IsValid())
				{
					plugin.SetASELAircraft(selectedRt);
				}
			}

		private:
			EuroScopePlugIn::CFlightPlan selectedFp;
			EuroScopePlugIn::CRadarTarget selectedRt;
		};

	public:
		static void CallEsFunction(
			CString callsign, int functionId, POINT point, RECT area,
			Screen::ScreenWrapper& screen)
		{
			auto& plugin = Plugin::PluginEnvironment::Shared().GetPlugin();
			SelectionRestorer restorer;

			plugin.SetASELAircraft(plugin.FlightPlanSelect(callsign));
			screen.StartTagFunction(callsign, nullptr, 0, "", nullptr, functionId, point, area);
			restorer.Restore();
		}
	};
}
