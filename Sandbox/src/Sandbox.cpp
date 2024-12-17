#include <memory>
#include "Palmy.h"


namespace Sandbox {
	class SandboxApp :public Palmy::Application {
	public:
		SandboxApp() :
			Palmy::Application("Sandbox")
		{

		}
	};
}

Palmy::Application* Palmy::Create() {

	return new Sandbox::SandboxApp();
}

