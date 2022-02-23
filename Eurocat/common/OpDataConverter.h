#pragma once

#include "base/pch.h"

namespace Eurocat::Common
{
	class OpDataConverter
	{
	public:
		static CString FromEsFormat(CString original)
		{
			CString result = original;

			// Remove the indicator of Eurocat label data ("/")
			if (result.Left(1) == "/")
			{
				result = result.Mid(1);
			}

			// Up to ten alphanumeric characters
			if (result.GetLength() > 10)
			{
				result = result.Left(10);
			}

			// Must be upper case
			result = result.MakeUpper();

			return result;
		}

		static CString ToEsFormat(CString str)
		{
			return str.IsEmpty() ? "" : "/" + str;
		}
	};
}
