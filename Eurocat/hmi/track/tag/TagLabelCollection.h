#pragma once

#include "hmi/track/tag/label/ITagLabel.h"

namespace Eurocat::Hmi::Track
{
	typedef std::vector<std::vector<std::shared_ptr<ITagLabel>>> TagLabelCollection;
}
