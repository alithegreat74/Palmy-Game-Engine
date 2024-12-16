#include "Application.h"

namespace Palmy {
	Application::Application():
		m_Window()
	{
		
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		m_Window.Update();
	}
	
}

