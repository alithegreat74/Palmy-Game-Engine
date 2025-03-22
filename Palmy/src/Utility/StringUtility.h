#pragma once
#include <string>
namespace Palmy
{
	class StringUtility {
	public:
		inline static std::string Remove(std::string& original, const std::string& toRemove) {
			auto it = original.find(toRemove);
			std::string out = original.substr(0, it) + original.substr(it + toRemove.size(), original.size());
			return out;
		}

	};
}