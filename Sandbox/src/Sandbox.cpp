#include <memory>
#include "Palmy.h"


namespace Sandbox {
	class SandboxApp :public Palmy::Application {

	};
}

Palmy::Application* Palmy::Create() {
	return new Sandbox::SandboxApp();
}

