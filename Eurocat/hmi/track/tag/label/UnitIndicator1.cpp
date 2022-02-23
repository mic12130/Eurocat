#include "base/pch.h"

#include "hmi/track/tag/label/UnitIndicator1.h"

#include "hmi/track/tag/label_content/StringContent.h"
#include "common/unit/RflConverter.h"

using namespace Eurocat::Common::Unit;
using namespace Eurocat::Hmi::Unit;

namespace Eurocat::Hmi::Track
{
	UnitIndicator1::UnitIndicator1(IFlightPlanDataProvider& data, UnitDisplayMode unit)
		: data(data), unit(unit)
	{
	}

	std::shared_ptr<ITagLabelContent> UnitIndicator1::GetTagLabelContent()
	{
		RflModel rfl = RflConverter::GetRflFromEsFormat(data.GetRfl());
		CString str = " ";

		if (unit == UnitDisplayMode::Imperial && rfl.isMeter)
		{
			str = "#";
		}
		else if (unit == UnitDisplayMode::Metric && !rfl.isMeter)
		{
			str = "#";
		}

		return std::make_shared<StringContent>(str);
	}
}
