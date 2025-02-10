#pragma once
#include <iostream>
#include <memory>
#include "Window.h"
#include "../Layer/LayerStack.h"
#include "ResourceManager.h"

namespace Palmy {

	class Application {
	public:
		Application(const std::string& applicationName = "");
		virtual ~Application() = default;
		virtual void Run();
		virtual void OnEvent(Event& e);
		virtual void AttachLayer(std::shared_ptr<Layer> layer);
	protected:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<LayerStack> m_LayerStack;
		std::unique_ptr<ResourceManager> m_ResourceManager;
	};

	Application* Create();
}