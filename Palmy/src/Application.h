#pragma once
#include <iostream>
#include "Window.h"
namespace Palmy {

	class Application {
	public:
		Application();
		virtual ~Application();
		virtual void Run();
	private:
		Window m_Window;
	};

	Application* Create();
}