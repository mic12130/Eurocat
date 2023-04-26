#pragma once

#include "base/pch.h"

struct DupeWarning
{
	DupeWarning(CString code, std::vector<CString> targetIds)
		: code(code), targetIds(targetIds)
	{
	}

	CString code;
	std::vector<CString> targetIds;
};

struct BuiltinWarning
{
	BuiltinWarning(CString targetId, bool isClam, bool isRam)
		: targetId(targetId), isClam(isClam), isRam(isRam)
	{
	}

	CString targetId;
	bool isClam = false;
	bool isRam = false;
};