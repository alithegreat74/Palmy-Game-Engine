#include "pch.h"
#include "UUID.h"
#include <string>
namespace Palmy {
	uint32_t UUID::CreateId(const std::string& filepath) {
		std::lock_guard<std::mutex>lock(s_IdMutex);
		uint32_t id = static_cast<uint32_t>(std::hash<std::string>{}(filepath));
		
		s_UniqueIds.insert(id);
		return id;
	}
}