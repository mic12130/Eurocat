#pragma once

#include "screen/IScreenEventHandler.h"

namespace Eurocat::Screen
{
	class EurocatScreen final : public EuroScopePlugIn::CRadarScreen
	{
	public:
		EurocatScreen(
			std::vector<std::shared_ptr<IScreenEventHandler>>& screenEventHandlers
		);

		void OnAsrContentToBeClosed() override;
		void OnRefresh(HDC hDC, int Phase) override;
		void OnOverScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area) override;
		void OnClickScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button) override;
		void OnMoveScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, bool Released) override;

	private:
		std::vector<std::shared_ptr<IScreenEventHandler>>& screenEventHandlers;
	};
}
