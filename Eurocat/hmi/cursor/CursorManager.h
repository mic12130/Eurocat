#pragma once

#include "hmi/cursor/ICursorManager.h"

namespace Eurocat::Hmi::Cursor
{
	class CursorManager : public ICursorManager
	{
	public:
		static std::shared_ptr<CursorManager> shared;

		void OnRender() override;
		void OnScreenToBeClosed() override;
		void SetCursorType(CursorType type) override;

	private:
		bool isInitialized = false;
	};
}
