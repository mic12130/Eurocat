#pragma once

namespace Eurocat::Common::Unit
{
	class RflModel
	{
	public:
		RflModel(int value, bool isMeter)
			: value(value), isMeter(isMeter)
		{
		}

		const int value;
		const bool isMeter;
	};
}
