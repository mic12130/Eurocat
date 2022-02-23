#include "base/pch.h"

#include "common/unit/RflConverter.h"

namespace Eurocat::Common::Unit
{
	const std::map<int, int> RflConverter::kRecognizedMetricRfls = {
		{48900, 14900}, {46900, 14300}, {44900, 13700}, {43000, 13100},
		{41100, 12500}, {40100, 12200}, {39100, 11900}, {38100, 11600},
		{37100, 11300}, {36100, 11000}, {35100, 10700}, {34100, 10400},
		{33100, 10100}, {32100, 9800}, {31100, 9500}, {30100, 9200},
		{29100, 8900}, {27600, 8400}, {26600, 8100}, {25600, 7800},
		{24600, 7500}, {23600, 7200}, {22600, 6900}, {21700, 6600},
		{20700, 6300}, {19700, 6000}, {18700, 5700}, {17700, 5400},
		{16700, 5100}, {15700, 4800}, {14800, 4500}, {13800, 4200},
		{12800, 3900}, {11800, 3600}, {10800, 3300}, {9800, 3000},
		{8900, 2700}, {7900, 2400}, {6900, 2100}, {5900, 1800},
		{4900, 1500}, {3900, 1200}, {3000, 900}, {2000, 600} };

	RflModel RflConverter::GetRflFromEsFormat(int value)
	{
		for (auto const& alt : kRecognizedMetricRfls)
		{
			if (alt.first == value)
			{
				return RflModel(alt.second, true);
			}
		}

		return RflModel(value, false);
	}

	int RflConverter::RestoreRflToEsFormat(RflModel rfl)
	{
		if (rfl.isMeter == false)
		{
			return rfl.value;
		}

		for (auto const& alt : kRecognizedMetricRfls)
		{
			if (alt.second == rfl.value)
			{
				return alt.first;
			}
		}

		return int(rfl.value / 0.3048);
	}
}
