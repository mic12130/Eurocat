#pragma once

namespace Eurocat::Screen
{
	class WindowScalingInfo
	{
	public:
		static double GetScaleFactor();

	private:
		inline static bool isLoaded = false;
		inline static double scaleFactor = 0.0;
	};
}
