#pragma once

#include "plugin/extension/OpDataExtraction.h"

namespace Eurocat::Plugin
{
	class OpDataConverter
	{
	public:
		static CString FromEsFormat(const OpDataExtraction& original, char leadingChar);
		static OpDataExtraction ToEsFormat(CString str, char leadingChar);
	};
}
