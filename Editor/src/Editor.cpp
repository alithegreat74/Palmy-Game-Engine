#include <memory>
#include "Palmy.h"
#include <./src/Core/EntryPoint.h>
#include <Palmy.h>
#include <fstream>

namespace Sandbox {

	class EditorLayer :public Palmy::Layer {
	public:
		EditorLayer(const std::string& layerName = "Editor Layer") :
			Palmy::Layer(layerName)
		{
		}
		~EditorLayer() {}
		virtual void OnUpdate() {
			
		}
		virtual void OnEvent(Palmy::Event& event)override {

		}
		bool KeyWasPressed(const Palmy::KeyPressedEvent& event)
		{

		}

	private:

	};

	class EditorApp :public Palmy::Application {
	public:
		EditorApp() :
			Palmy::Application("Palmy Editor")
		{

		}
	};
}



Palmy::Application* Palmy::Create() {

	return new Sandbox::EditorApp();
}

