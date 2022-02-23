#include "base/pch.h"

#include "hmi/OptionDialog.h"

#include "common/unit/AltitudeConverter.h"
#include "common/unit/AltitudeFormatter.h"

using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Hmi
{
	IMPLEMENT_DYNAMIC(OptionDialog, CDialogEx)

	BEGIN_MESSAGE_MAP(OptionDialog, CDialogEx)
		ON_BN_CLICKED(IDOK, &OptionDialog::OnClickOk)
		ON_CBN_SELENDOK(IDC_COMBO_OPTION_UNIT, &OptionDialog::OnSelectedUnit)
	END_MESSAGE_MAP()

	OptionDialog::OptionDialog(
		Unit::UnitDisplayManager& unitDisplayManager,
		Track::TrackProfileManager& trackProfileManager,
		Track::OptionData& trackOption)
		: CDialogEx(OptionDialog::IDD, GetActiveWindow()),
		unitDisplayManager(unitDisplayManager),
		trackProfileManager(trackProfileManager),
		trackOption(trackOption)
	{
	}

	BOOL OptionDialog::OnInitDialog()
	{
		CDialogEx::OnInitDialog();
		::SetWindowText(m_hWnd, "Options");

		auto velCheckbox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_VEL));
		auto velMinuteComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_VEL));
		auto histCheckbox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_HIST));
		auto histCountComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_HIST));
		auto showFpTrackCheckbox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_FPASD));
		auto hidePsrCheckbox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_HIDE_PSR));
		auto altFilterHighField = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_OPTION_ALT_FILTER_HIGH));
		auto altFilterLowField = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_OPTION_ALT_FILTER_LOW));
		auto unitComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_UNIT));
		auto identComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_IDENT));
		auto extendedLabelCheckBox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_EXTENDED));
		auto sharedLabelCheckBox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_SHARED));

		// VEL
		CString velStr;
		velCheckbox->SetCheck(trackOption.enableVelocityVectorDisplay ? BST_CHECKED : BST_UNCHECKED);
		velStr.Format("%d", trackOption.velocityVectorMinutes);
		velMinuteComboBox->SetCurSel(velMinuteComboBox->FindString(-1, velStr));

		// HIST
		CString histStr;
		histCheckbox->SetCheck(trackOption.enableHistoryDotsDisplay ? BST_CHECKED : BST_UNCHECKED);
		histStr.Format("%d", trackOption.historyDotsCount);
		histCountComboBox->SetCurSel(histCountComboBox->FindString(-1, histStr));

		// FPASD
		showFpTrackCheckbox->SetCheck(trackOption.showFlightPlanTracks ? BST_CHECKED : BST_UNCHECKED);

		// Hide PSR symbol
		hidePsrCheckbox->SetCheck(trackOption.hidePsrSymbol ? BST_CHECKED : BST_UNCHECKED);

		// Altitude filter
		SetAltFilterField(altFilterHighField, trackOption.altitudeFilterHigh, unitDisplayManager.GetDefaultUnit());
		SetAltFilterField(altFilterLowField, trackOption.altitudeFilterLow, unitDisplayManager.GetDefaultUnit());

		// Unit
		if (unitDisplayManager.GetDefaultUnit() == Unit::UnitDisplayMode::Imperial)
		{
			unitComboBox->SetCurSel(unitComboBox->FindString(-1, "Imperial"));
		}
		else if (unitDisplayManager.GetDefaultUnit() == Unit::UnitDisplayMode::Metric)
		{
			unitComboBox->SetCurSel(unitComboBox->FindString(-1, "Metric"));
		}

		// Ident
		if (trackOption.identDisplayMode == Track::IdentDisplayMode::Acid)
		{
			identComboBox->SetCurSel(identComboBox->FindString(-1, "ACID"));
		}
		else if (trackOption.identDisplayMode == Track::IdentDisplayMode::Ssr)
		{
			identComboBox->SetCurSel(identComboBox->FindString(-1, "SSR"));
		}
		else if (trackOption.identDisplayMode == Track::IdentDisplayMode::TargetId)
		{
			identComboBox->SetCurSel(identComboBox->FindString(-1, "Target ID"));
		}

		// Extended label
		extendedLabelCheckBox->SetCheck(trackOption.enableExtendedLabel ? BST_CHECKED : BST_UNCHECKED);

		// Shared label
		sharedLabelCheckBox->SetCheck(trackOption.enableSharedLabel ? BST_CHECKED : BST_UNCHECKED);

		return TRUE;
	}

	void OptionDialog::DoDataExchange(CDataExchange* pDX)
	{
		CDialogEx::DoDataExchange(pDX);
	}

	void OptionDialog::OnClickOk()
	{
		auto velCheckbox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_VEL));
		auto velMinuteComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_VEL));
		auto histCheckbox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_HIST));
		auto histCountComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_HIST));
		auto showFpTrackCheckbox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_FPASD));
		auto hidePsrCheckbox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_HIDE_PSR));
		auto altFilterHighField = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_OPTION_ALT_FILTER_HIGH));
		auto altFilterLowField = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_OPTION_ALT_FILTER_LOW));
		auto unitComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_UNIT));
		auto identComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_IDENT));
		auto extendedLabelCheckBox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_EXTENDED));
		auto sharedLabelCheckBox = static_cast<CButton*>(GetDlgItem(IDC_CHECK_OPTION_SHARED));

		// VEL
		if ((velCheckbox->GetCheck() == BST_CHECKED) != trackOption.enableVelocityVectorDisplay)
		{
			trackOption.enableVelocityVectorDisplay = velCheckbox->GetCheck() == BST_CHECKED;
			trackProfileManager.ResetUserSetVel();
		}

		CString velMinuteStr;
		velMinuteComboBox->GetWindowText(velMinuteStr);
		trackOption.enableVelocityVectorDisplay = velCheckbox->GetCheck() == BST_CHECKED;
		trackOption.velocityVectorMinutes = std::stoi(velMinuteStr.GetString());

		// HIST
		CString histCountStr;
		histCountComboBox->GetWindowText(histCountStr);
		trackOption.enableHistoryDotsDisplay = histCheckbox->GetCheck() == BST_CHECKED;
		trackOption.historyDotsCount = std::stoi(histCountStr.GetString());

		// FPASD
		trackOption.showFlightPlanTracks = showFpTrackCheckbox->GetCheck() == BST_CHECKED;

		// Hide PSR symbol
		trackOption.hidePsrSymbol = hidePsrCheckbox->GetCheck() == BST_CHECKED;

		// Altitude filter
		CString altFilterHighStr, altFilterLowStr, unitStr;
		altFilterHighField->GetWindowText(altFilterHighStr);
		altFilterLowField->GetWindowText(altFilterLowStr);
		unitComboBox->GetWindowText(unitStr);

		if (unitStr == "Imperial")
		{
			trackOption.altitudeFilterHigh =
				(altFilterHighStr.IsEmpty()) ? -1 : std::stoi(altFilterHighStr.GetString()) * 100;
			trackOption.altitudeFilterLow =
				(altFilterLowStr.IsEmpty()) ? -1 : std::stoi(altFilterLowStr.GetString()) * 100;
		}
		else if (unitStr == "Metric")
		{
			trackOption.altitudeFilterHigh =
				altFilterHighStr.IsEmpty() ?
				-1 : AltitudeConverter::MeterToFeet(std::stoi(altFilterHighStr.GetString()) * 10);
			trackOption.altitudeFilterLow =
				altFilterLowStr.IsEmpty() ?
				-1 : AltitudeConverter::MeterToFeet(std::stoi(altFilterLowStr.GetString()) * 10);
		}

		// Unit
		if (unitStr == "Imperial")
		{
			unitDisplayManager.SetDefaultUnit(UnitDisplayMode::Imperial);
		}
		else if (unitStr == "Metric")
		{
			unitDisplayManager.SetDefaultUnit(UnitDisplayMode::Metric);
		}

		// Ident
		CString identStr;
		identComboBox->GetWindowText(identStr);
		if (identStr == "ACID")
		{
			trackOption.identDisplayMode = Track::IdentDisplayMode::Acid;
		}
		else if (identStr == "SSR")
		{
			trackOption.identDisplayMode = Track::IdentDisplayMode::Ssr;
		}
		else if (identStr == "Target ID")
		{
			trackOption.identDisplayMode = Track::IdentDisplayMode::TargetId;
		}

		// Extended label
		if ((extendedLabelCheckBox->GetCheck() == BST_CHECKED) != trackOption.enableExtendedLabel)
		{
			trackOption.enableExtendedLabel = extendedLabelCheckBox->GetCheck() == BST_CHECKED;
			trackProfileManager.ResetUserSetExtended();
		}

		// Shared label
		trackOption.enableSharedLabel = sharedLabelCheckBox->GetCheck() == BST_CHECKED;

		CDialogEx::OnOK();
	}

	void OptionDialog::OnSelectedUnit()
	{
		CString unitStr;
		auto unitComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_OPTION_UNIT));
		auto altFilterHighField = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_OPTION_ALT_FILTER_HIGH));
		auto altFilterLowField = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_OPTION_ALT_FILTER_LOW));
		unitComboBox->GetLBText(unitComboBox->GetCurSel(), unitStr);

		if (unitStr == "Imperial")
		{
			SetAltFilterField(altFilterHighField, trackOption.altitudeFilterHigh, UnitDisplayMode::Imperial);
			SetAltFilterField(altFilterLowField, trackOption.altitudeFilterLow, UnitDisplayMode::Imperial);
		}
		else if (unitStr == "Metric")
		{
			SetAltFilterField(altFilterHighField, trackOption.altitudeFilterHigh, UnitDisplayMode::Metric);
			SetAltFilterField(altFilterLowField, trackOption.altitudeFilterLow, UnitDisplayMode::Metric);
		}
	}

	void OptionDialog::SetAltFilterField(CEdit* field, int optionValue, Unit::UnitDisplayMode unit)
	{
		if (optionValue == -1)
		{
			field->SetWindowText("");
		}
		else
		{
			AltitudeFormatter formatter(unit);

			if (unit == UnitDisplayMode::Imperial)
			{
				field->SetWindowText(formatter.StringFromAltitude(optionValue));
			}
			else if (unit == UnitDisplayMode::Metric)
			{
				int meters = AltitudeConverter::FeetToMeter(optionValue);
				field->SetWindowText(formatter.StringFromAltitude(meters));
			}
		}
	}
}
