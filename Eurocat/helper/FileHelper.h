#pragma once

#include "base/pch.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

class FileHelper
{
public:
	static CString GetFileName()
	{
		char fileName[MAX_PATH];
		GetModuleFileName((HINSTANCE)&__ImageBase, fileName, _countof(fileName));

		return fileName;
	}
};
