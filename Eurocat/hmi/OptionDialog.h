#pragma once

#include <afxdialogex.h>
#include "res/resource.h"
#include "hmi/unit/UnitDisplayManager.h"
#include "track/profile/TrackProfileManager.h"
#include "track/option/OptionData.h"

namespace Eurocat::Hmi
{
	// Provides a temporary place where user can configure the plugin
	// This dialog will be removed once the Eurocat-style config UI is
	// completed (Setup Window, General Information Window etc)
	class OptionDialog : public CDialogEx
	{
		DECLARE_DYNAMIC(OptionDialog)
		DECLARE_MESSAGE_MAP()

	public:
		OptionDialog(
			Unit::UnitDisplayManager& unitDisplayManager,
			Track::TrackProfileManager& trackProfileManager,
			Track::OptionData& trackOption
		);

		BOOL OnInitDialog() override;
		void DoDataExchange(CDataExchange* pDX) override;

		afx_msg void OnClickOk();
		afx_msg void OnSelectedUnit();

	private:
		enum { IDD = IDD_DIALOG_OPTION };

		void SetAltFilterField(CEdit* field, int optionValue, Unit::UnitDisplayMode unit);

		Unit::UnitDisplayManager& unitDisplayManager;
		Track::TrackProfileManager& trackProfileManager;
		Track::OptionData& trackOption;
	};
}
