#pragma once
#include <iostream>
#include <memory>
#include "Window.h"
#include "../Layer/LayerStack.h"
#include "AssetMetaGenerator.h"
#include "ResourceManager.h"
#include "../Rendering/Renderer2D.h"

namespace Palmy {

	class Application {
	public:
		Application(const std::string& applicationName = "Application", float width = 1280.0f, float height = 720.0f);
		virtual ~Application() = default;
		virtual void Run();
		virtual void OnEvent(Event& e);
		virtual void AttachLayer(std::shared_ptr<Layer> layer);
	protected:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ResourceManager> m_ResourceManager;
		std::shared_ptr<Renderer2D> m_Renderer;
	private:
		std::unique_ptr<LayerStack> m_LayerStack;
	};

	Application* Create();
}