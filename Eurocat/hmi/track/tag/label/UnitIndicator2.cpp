#include "base/pch.h"

#include "hmi/track/tag/label/UnitIndicator2.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	UnitIndicator2::UnitIndicator2()
	{
	}

	std::shared_ptr<ITagLabelContent> UnitIndicator2::GetTagLabelContent()
	{
		return std::make_shared<StringContent>("");
	}
}
