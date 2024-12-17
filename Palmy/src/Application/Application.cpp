#include "Application.h"

namespace Palmy {
	Application::Application(const std::string& applicationName)
	{
		m_Window = Window::Create(applicationName);
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		m_Window->Update();
	}
	
}

