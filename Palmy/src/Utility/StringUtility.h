#pragma once
#include <string>
#include <codecvt>

namespace Palmy
{
	class StringUtility {
	public:
		inline static std::string Remove(std::string& original, const std::string& toRemove) {
			auto it = original.find(toRemove);
			std::string out = original.substr(0, it) + original.substr(it + toRemove.size(), original.size());
			return out;
		}
		inline static std::string ConvertWideString(std::wstring&& wideString)
		{
#ifdef WINDOWS
			int stringSize = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, nullptr, 0, nullptr, nullptr);
			std::string narrowString(stringSize, 0);
			WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, &narrowString[0], stringSize, nullptr, nullptr);
			narrowString.pop_back();
			return narrowString;
#else
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			+return converter.to_bytes(wideString);
#endif 
		}
	};
}