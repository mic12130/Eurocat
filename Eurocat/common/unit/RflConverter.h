#pragma once

#include "common/unit/RflModel.h"

namespace Eurocat::Common::Unit
{
	class RflConverter
	{
	public:
		// Convert the original RFL output from ES API
		// into a RFL buffer with unit info
		// Notes: This method will check whether the given altitude is in meter
		// by matching it with the recognized metric RFL list
		static RflModel GetRflFromEsFormat(int value);

		// Convert the RFL buffer with unit info
		// into a simple feet altitude that can be accepted by ES API
		//
		// - RFLs in meter and found in the recognized metric RFL list
		// will be converted to correlative feet altitudes
		// - RFLs in meter but not found in the recognized metric RFL list
		// will be converted to feet by simply dividing 0.3048
		static int RestoreRflToEsFormat(RflModel rfl);

	private:
		static const std::map<int, int> kRecognizedMetricRfls;
	};
}
