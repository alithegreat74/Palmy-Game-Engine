#pragma once
#include <iostream>
#include "Window.h"
namespace Palmy {

	class Application {
	public:
		Application(const std::string& applicationName = "");
		virtual ~Application();
		virtual void Run();
	private:
		std::unique_ptr<Window> m_Window;
	};

	Application* Create();
}