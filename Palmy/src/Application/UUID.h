#pragma once
#include <cstdint>
#include <unordered_set>

namespace Palmy
{
	class UUID {
	public:
		static uint64_t CreateId();
		static void AddId(uint64_t id);
	private:
		inline static std::unordered_set<uint64_t> s_UniqueIds = std::unordered_set<uint64_t>();
	};
}