#pragma once

namespace Eurocat::Config
{
	template <typename T>
	class ISettingItemValidator
	{
	public:
		virtual ~ISettingItemValidator() = default;
		virtual bool IsValid(T value, CString& error) = 0;
	};

	class IntegerRangeValidator : public ISettingItemValidator<int>
	{
	public:
		IntegerRangeValidator(int max, int min) : maxValue(max), minValue(min)
		{
		}

		bool IsValid(int value, CString& error) override
		{
			if (value >= minValue && value <= maxValue)
			{
				return true;
			}

			error.Format("Value out of range (min: %d, max: %d)", minValue, maxValue);
			return false;
		}

	private:
		int maxValue;
		int minValue;
	};
}