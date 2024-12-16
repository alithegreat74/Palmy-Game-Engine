#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Palmy {
	class Log {
	public:
		static void Init();

		inline static const std::shared_ptr<spdlog::logger>& GetEngineLogger(){ return s_EngineLogger; }
		inline static const std::shared_ptr<spdlog::logger>& GetClientLogger(){ return s_ClientLogger; }
	private:
		inline static std::shared_ptr<spdlog::logger> s_EngineLogger = nullptr;
		inline static std::shared_ptr<spdlog::logger> s_ClientLogger = nullptr;
	};

#define ENGINE_LOG(...) Log::GetEngineLogger()->info(__VA_ARGS__);
#define ENGINE_WARNING(...) Log::GetEngineLogger()->warn(__VA_ARGS__);
#define ENGINE_ERROR(...) Log::GetEngineLogger()->error(__VA_ARGS__);

#define CLIENT_LOG(...) Log::GetClientLogger()->info(__VA_ARGS__);
#define CLIENT_WARNING(...) Log::GetClientLogger()->warn(__VA_ARGS__);
#define CLIENT_ERROR(...) Log::GetClientLogger()->error(__VA_ARGS__);

}