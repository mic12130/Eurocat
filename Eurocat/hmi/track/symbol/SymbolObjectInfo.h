#pragma once

#include "base/pch.h"

namespace Eurocat::Hmi::Track
{
	// Information of symbol screen object
	struct SymbolObjectInfo
	{
		SymbolObjectInfo(CString objectId, CString message) : objectId(objectId), message(message)
		{
		}

		CString objectId;
		CString message;
	};
}
