#pragma once

#include "base/pch.h"

#include "hmi/track/tag/label_content/ITagLabelContent.h"

namespace Eurocat::Hmi::Track
{
	class ITagLabel
	{
	public:
		virtual ~ITagLabel() = default;
		virtual std::shared_ptr<ITagLabelContent> GetTagLabelContent() = 0;
	};
}
