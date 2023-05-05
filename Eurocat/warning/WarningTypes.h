#pragma once

#include "base/pch.h"

struct DupeWarning
{
	DupeWarning(CString code, std::vector<CString> targetIds)
		: code(code), targetIds(targetIds)
	{
	}

	std::string Description()
	{
		std::string str = std::format("Code: {}, Targets:", code.GetString());
		for (auto& id : targetIds) { str += " " + id; }
		return str;
	}

	CString code;
	std::vector<CString> targetIds;
};

inline bool operator==(const DupeWarning& lhs, const DupeWarning& rhs)
{
	return lhs.code == rhs.code && lhs.targetIds == rhs.targetIds;
}

struct BuiltinWarning
{
	BuiltinWarning(CString targetId, bool isClam, bool isRam)
		: targetId(targetId), isClam(isClam), isRam(isRam)
	{
	}

	std::string Description()
	{
		return std::format("Target: {}, CLAM: {}, RAM: {}", targetId.GetString(), isClam, isRam);
	}

	CString targetId;
	bool isClam = false;
	bool isRam = false;
};

inline bool operator==(const BuiltinWarning& lhs, const BuiltinWarning& rhs)
{
	auto lhsTuple = std::tie(lhs.targetId, lhs.isClam, lhs.isRam);
	auto rhsTuple = std::tie(rhs.targetId, rhs.isClam, rhs.isRam);
	return lhsTuple == rhsTuple;
}