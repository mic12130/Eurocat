#include "base/pch.h"

#include "hmi/track/tag/label/SpaceLabel.h"

#include "hmi/track/tag/label_content/StringContent.h"

namespace Eurocat::Hmi::Track
{
	std::shared_ptr<ITagLabelContent> SpaceLabel::GetTagLabelContent()
	{
		return std::make_shared<StringContent>(" ");
	}
}
