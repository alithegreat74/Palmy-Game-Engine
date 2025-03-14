#include "pch.h"
#include "UUID.h"

namespace Palmy {
	uint64_t UUID::CreateId() {
		std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<uint64_t>dist;
		uint64_t randomNumber = 0;
		do {
			randomNumber = dist(mt);
		} while (s_UniqueIds.find(randomNumber) != s_UniqueIds.end());
		s_UniqueIds.emplace(randomNumber);
		return randomNumber;
	}
	void UUID::AddId(uint64_t id) {
		if (s_UniqueIds.find(id) != s_UniqueIds.end())
			return;
		s_UniqueIds.emplace(id);
	}
}