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
};
