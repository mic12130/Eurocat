#pragma once

#include "base/pch.h"

#include <vector>
#include <sstream>

class StringHelper
{
public:
	static std::vector<CString> GetComponents(CString fullString, char split)
	{
		std::string str = fullString;
		std::stringstream ss(str);
		std::string segment;
		std::vector<CString> contentList;

		while (std::getline(ss, segment, split))
		{
			contentList.push_back(segment.c_str());
		}

		return contentList;
	}

	static CString Join(CString separator, const std::vector<CString>& arr)
	{
		if (arr.empty())
		{
			return "";
		}

		CString result = arr[0];
		if (arr.size() > 1)
		{
			for (int i = 1; i < arr.size(); i++)
			{
				result = result + separator + arr[i];
			}
		}

		return result;
	}
};
