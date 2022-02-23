#pragma once

#include "pch.h"

#include "hmi/track/tag/label/ITagLabel.h"
#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	inline auto GetStringContent(std::shared_ptr<ITagLabel> label) -> std::shared_ptr<StringContent>
	{
		return std::static_pointer_cast<StringContent>(label->GetTagLabelContent());
	}
}
