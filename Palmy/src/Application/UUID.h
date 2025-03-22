#pragma once
#include <cstdint>
#include <unordered_set>
#include <mutex>

namespace Palmy
{
	class UUID {
	public:
		static uint32_t CreateId(const std::string& name);
	private:
		inline static std::unordered_set<uint32_t> s_UniqueIds = std::unordered_set<uint32_t>();
		inline static std::mutex s_IdMutex;
	};
}