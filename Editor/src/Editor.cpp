#include <memory>
#include "Palmy.h"
#include <./src/Core/EntryPoint.h>
#include <fstream>

namespace Sandbox {

	class EditorLayer :public Palmy::Layer {
	public:
		EditorLayer(const std::string& layerName) :
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
			AttachLayer(std::make_shared<EditorLayer>("Editor Layer"));
		}
	};
}



Palmy::Application* Palmy::Create() {

	return new Sandbox::EditorApp();
}

