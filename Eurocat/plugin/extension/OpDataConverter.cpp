#include "base/pch.h"

#include "plugin/extension/OpDataConverter.h"

#include "helper/StringHelper.h"

namespace Eurocat::Plugin
{
	CString OpDataConverter::FromEsFormat(const OpDataExtraction& original, char leadingChar)
	{
		std::vector<CString> components;

		// Append assigned heading
		if (int heading = original.assignedHeading; heading != 0)
		{
			CString str;
			str.Format("H%03d", heading);
			components.push_back(str);
		}

		// Append assigned speed
		if (int speed = original.assignedSpeed; speed != 0)
		{
			CString str;
			str.Format("S%d", speed);
			components.push_back(str);
		}

		// Append assigned mach
		if (int mach = original.assignedMach; mach != 0)
		{
			CString str;
			str.Format("M%d", mach);
			components.push_back(str);
		}

		// Append direct point
		if (CString point = original.dctPoint; point != "")
		{
			components.push_back(point);
		}

		// Append text
		if (CString text = original.text; text != "")
		{
			// Remove the indicator of Eurocat label data ("/" by default)
			if (text.Left(1) == leadingChar)
			{
				components.push_back(text.Mid(1));
			}
			else
			{
				components.push_back(text);
			}
		}

		CString result = StringHelper::Join(" ", components);
		result = result.MakeUpper(); // Must be upper case

		return result;
	}

	OpDataExtraction OpDataConverter::ToEsFormat(CString str, char leadingChar)
	{
		OpDataExtraction result;
		std::vector<CString> remainingTexts;
		std::regex headingExp("(?:H|h)([0-9]{3})");
		std::regex speedExp("(?:S|s)([0-9]{2,3})");
		std::regex machExp("(?:M|m)([0-9]{2,3})");

		for (auto& component : StringHelper::GetComponents(str, ' '))
		{
			std::smatch matched;
			std::string std_str(component.GetString());

			if (std::regex_search(std_str, matched, headingExp))
			{
				result.assignedHeading = stoi(matched.str(1));
			}
			else if (std::regex_search(std_str, matched, speedExp))
			{
				result.assignedSpeed = stoi(matched.str(1));
			}
			else if (std::regex_search(std_str, matched, machExp))
			{
				result.assignedMach = stoi(matched.str(1));
			}
			else
			{
				remainingTexts.push_back(component.MakeUpper());
			}
		}

		result.text = StringHelper::Join(" ", remainingTexts);

		if (result.text != "")
		{
			// Make upper and and add slash prefix (to avoid transforming to assigned data)
			result.text = leadingChar + result.text.MakeUpper();
		}

		return result;
	}
}
