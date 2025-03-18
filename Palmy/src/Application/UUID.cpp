#include "pch.h"
#include "UUID.h"

namespace Palmy {
	uint32_t UUID::CreateId() {
		std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<uint32_t>dist;
		uint64_t randomNumber = 0;
		std::lock_guard<std::mutex>lock(s_IdMutex);
		do {
			randomNumber = dist(mt);
		} while (s_UniqueIds.find(randomNumber) != s_UniqueIds.end());
		s_UniqueIds.emplace(randomNumber);
		return randomNumber;
	}
	void UUID::AddId(uint32_t id) {
		if (s_UniqueIds.find(id) != s_UniqueIds.end())
			return;
		s_UniqueIds.emplace(id);
	}
}