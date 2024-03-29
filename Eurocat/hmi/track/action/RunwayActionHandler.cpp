#include "base/pch.h"

#include "hmi/track/action/RunwayActionHandler.h"

#include "hmi/track/action/EuroScopeFunctionHelper.h"
#include "plugin/input/PopupMenu.h"
#include "plugin/extension/FlightPlanExtension.h"
#include "plugin/PluginAccess.h"

using namespace Eurocat::Screen;
using namespace Eurocat::Plugin;
using namespace Eurocat::Plugin::Input;

namespace Eurocat::Hmi::Track
{
	void RunwayActionHandler::OnTriggerAction(
		const TrackProfile& trackProfile,
		Screen::ScreenWrapper& screen,
		Screen::MouseButton button,
		POINT point, RECT area)
	{
		if (button == MouseButton::Left)
		{
			auto fp = PluginAccess::Shared().GetPlugin().FlightPlanSelect(trackProfile.flightPlanId.value());
			auto fpExt = FlightPlanExtension(fp);

			if (!fpExt.GetWritable())
			{
				return;
			}

			callsignForPopup = trackProfile.flightPlanId.value();
			destForPopup = fp.GetFlightPlanData().GetDestination();
			auto runways = GetActiveArrivalRunways(destForPopup);

			if (!runways.empty())
			{
				auto popupMenu = std::make_shared<PopupMenu>();
				popupMenu->SetTitle("");
				popupMenu->delegate = shared_from_this();

				for (auto& runway : runways)
				{
					popupMenu->AddItem(PopupMenuItem(runway));
				}

				popupMenu->Show(point, area);
			}
		}
	}

	void RunwayActionHandler::OnSelectItem(Plugin::Input::PopupMenuItem item, POINT point, RECT rect)
	{
		auto fp = PluginAccess::Shared().GetPlugin().FlightPlanSelect(callsignForPopup);

		if (!fp.IsValid())
		{
			return;
		}

		std::string star = fp.GetFlightPlanData().GetStarName();
		std::string arr_rwy = fp.GetFlightPlanData().GetArrivalRwy();
		std::string route = fp.GetFlightPlanData().GetRoute();
		std::string selected = item.text.GetString();
		std::string dest = destForPopup.GetString();

		if (!star.empty() || !arr_rwy.empty())
		{
			// If either STAR or arrival runway exists, we will replace the arrival
			// section (e.g. ZGGG/02L) with the new one with an updated runway
			//
			// Since lookbehind (?<=exp) is not supported, the leading space will be
			// also matched and we will add it back in the replacement

			std::regex arr_regex("\\s\\S*$");
			std::string new_arr = " " + (star.empty() ? dest : star) + "/" + selected;
			std::string new_route = std::regex_replace(route, arr_regex, new_arr);
			fp.GetFlightPlanData().SetRoute(new_route.c_str());
			fp.GetFlightPlanData().AmendFlightPlan();
		}
		else
		{
			fp.GetFlightPlanData().SetRoute((route + " " + dest + "/" + selected).c_str());
			fp.GetFlightPlanData().AmendFlightPlan();
		}
	}

	std::vector<CString> RunwayActionHandler::GetActiveArrivalRunways(CString icao)
	{
		auto& plugin = PluginAccess::Shared().GetPlugin();
		std::vector<CString> result;

		for (auto element = plugin.SectorFileElementSelectFirst(EuroScopePlugIn::SECTOR_ELEMENT_RUNWAY);
			element.IsValid();
			element = plugin.SectorFileElementSelectNext(element, EuroScopePlugIn::SECTOR_ELEMENT_RUNWAY))
		{
			// It looks like an ES API issue that GetAirportName() would always
			// return with a space appended (e.g. "ZSSS HONGQIAO ", "ZBAA ")
			// No impact on codes below, just a reminder :)
			CString apt = element.GetAirportName();

			if (apt.Left(4) == icao)
			{
				if (element.IsElementActive(false, 0))
				{
					result.push_back(element.GetRunwayName(0));
				}
				else if (element.IsElementActive(false, 1))
				{
					result.push_back(element.GetRunwayName(1));
				}
			}
		}

		return result;
	}
}
