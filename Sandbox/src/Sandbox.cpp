#include <memory>
#include "Palmy.h"


namespace Sandbox {
	class ExampleLayer :public Palmy::Layer {
	public:
		ExampleLayer(const std::string& layerName = "New Layer"):
			Palmy::Layer(layerName)
		{

		}
		~ExampleLayer(){}

		virtual void OnAttach() {

		}
		virtual void OnUpdate() {

		}
		virtual void OnEvent(Palmy::Event& event) {
		}
	};

	class SandboxApp :public Palmy::Application {
	public:
		SandboxApp() :
			Palmy::Application("Sandbox")
		{
			m_LayerStack->AttachLayer(std::make_shared<ExampleLayer>("Example Layer"));
		}
	};
}



Palmy::Application* Palmy::Create() {

	return new Sandbox::SandboxApp();
}

