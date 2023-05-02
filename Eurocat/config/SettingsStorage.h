#pragma once

namespace Eurocat::Config
{
	class SettingsStorage
	{
	public:
		SettingsStorage();
		void Load(std::string path);

		template <typename T>
		std::optional<T> GetValue(CString key) const;

	private:
		void AddRecognizedKeys();

		std::vector<CString> recognizedKeys;
		std::map<CString, CString> valueMap;
	};

	template<typename T>
	inline std::optional<T> SettingsStorage::GetValue(CString key) const
	{
		static_assert(
			std::is_same<T, int>::value ||
			std::is_same<T, double>::value ||
			std::is_same<T, CString>::value,
			"T must be int, double or CString");

		if (valueMap.contains(key))
		{
			CString str = valueMap.at(key);

			if constexpr (std::is_same<T, int>::value)
			{
				return std::make_optional<int>(std::stoi(str.GetString()));
			}
			else if constexpr (std::is_same<T, double>::value)
			{
				return std::make_optional<double>(std::stod(str.GetString()));
			}
			else if constexpr (std::is_same<T, CString>::value)
			{
				return std::make_optional<CString>(str);
			}
		}

		return std::nullopt;
	}
}