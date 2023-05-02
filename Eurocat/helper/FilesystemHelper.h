#pragma once

#include "base/pch.h"

class FilesystemHelper
{
public:
	static std::string GetDllPath()
	{
		CString dllPath;
		CString folderPath;
		WCHAR dllPathChar[MAX_PATH];
		GetModuleFileNameW((HINSTANCE)&__ImageBase, dllPathChar, _countof(dllPathChar));
		dllPath = (LPCWSTR)dllPathChar;

		return dllPath.GetString();
	}

	static std::string GetDllDirPath()
	{
		std::filesystem::path currentPath(GetDllPath());
		return currentPath.parent_path().string();
	}
};