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


}
#define ENGINE_LOG(...) Palmy::Log::GetEngineLogger()->info(__VA_ARGS__);
#define ENGINE_WARNING(...) Palmy::Log::GetEngineLogger()->warn(__VA_ARGS__);
#define ENGINE_ERROR(...) Palmy::Log::GetEngineLogger()->error(__VA_ARGS__);

#define CLIENT_LOG(...) Palmy::Log::GetClientLogger()->info(__VA_ARGS__);
#define CLIENT_WARNING(...) Palmy::Log::GetClientLogger()->warn(__VA_ARGS__);
#define CLIENT_ERROR(...) Palmy::Log::GetClientLogger()->error(__VA_ARGS__);