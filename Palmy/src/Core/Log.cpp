#include "pch.h"
#include "Log.h"

namespace Palmy {
	void Log::Init() {
		s_EngineLogger = spdlog::stdout_color_mt("Engine");
		s_ClientLogger = spdlog::stdout_color_mt("Client");

		s_EngineLogger->set_pattern("%$ [%D : %r] %n >>>>>>>>>>>>>> %v%$");
		s_ClientLogger->set_pattern("%$ [%D : %r] %n >>>>>>>>>>>>>> %v%$");

	}
}
