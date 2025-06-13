#include <memory>
#include "Palmy.h"
#include <fstream>


namespace Sandbox {

	

	class ExampleLayer :public Palmy::Layer {
	public:
		ExampleLayer(const std::string& layerName = "New Layer"):
			Palmy::Layer(layerName)
		{
			m_Texture = Palmy::ResourceManager::GetTexture2D(710627734);
		}
		~ExampleLayer(){}

		virtual void OnUpdate() {
				
			m_Renderer->RenderQuad(Palmy::Transform2D(), m_Texture);
		}
	private:
		std::shared_ptr<Palmy::Texture2D> m_Texture;
	};

	class SandboxApp :public Palmy::Application {
	public:
		SandboxApp() :
			Palmy::Application("Sandbox")
		{
			AttachLayer(std::make_shared<ExampleLayer>("Example Layer"));
		}
	};
}



Palmy::Application* Palmy::Create() {

	return new Sandbox::SandboxApp();
}

