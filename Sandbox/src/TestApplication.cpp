#include <memory>
#include "Palmy.h"
#include <fstream>


namespace TestApplication {

	

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
			Palmy::EventHandler::Handle<Palmy::WindowResizedEvent>(ENGINE_BIND(ExampleLayer::OnWindowResized),event);
		}

		bool OnWindowResized(const Palmy::WindowResizedEvent& event) {
			CLIENT_LOG("Window Resized to Width:{0}, Height:{1}", event.m_Width, event.m_Height);
			return true;
		}
	};

	class TestApplication :public Palmy::Application {
	public:
		TestApplication() :
			Palmy::Application("TestApplication")
		{
			m_LayerStack->AttachLayer(std::make_shared<ExampleLayer>("Example Layer"));

		}
	};
}



Palmy::Application* Palmy::Create() {

	return new TestApplication::TestApplication();
}

