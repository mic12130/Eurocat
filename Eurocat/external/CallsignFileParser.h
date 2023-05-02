#pragma once

#include "base/pch.h"

namespace Eurocat::External
{
	class CallsignFileParser
	{
	public:
		static std::map<CString, CString> Parse(std::string path);
	};
}