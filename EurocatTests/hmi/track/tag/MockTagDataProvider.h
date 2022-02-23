#pragma once

#include "pch.h"

#include "hmi/track/tag/render_data/ITagDataProvider.h"

namespace Eurocat::Hmi::Track
{
	class MockTagDataProvider : public ITagDataProvider
	{
	public:
		MOCK_METHOD(bool, CanOverrideFilter, (), (override));
		MOCK_METHOD(TagLabelCollection, GetLabels, (), (override));
		MOCK_METHOD(TagAlertData, GetAlertData, (), (override));
		MOCK_METHOD(bool, GetIsFlashing, (), (override));
		MOCK_METHOD(bool, GetIsRepositioning, (), (override));
		MOCK_METHOD(CString, GetProfileId, (), (override));
		MOCK_METHOD((std::tuple<int, int>), GetOffset, (), (override));
		MOCK_METHOD(Common::Coordinate, GetPosition, (), (override));
	};
}
