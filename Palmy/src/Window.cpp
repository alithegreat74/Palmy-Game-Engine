#include "Window.h"

namespace Palmy {
	Window::Window(WindowInfo info):
		m_WindowInfo(info)
	{
		std::cout << "Creating A Window" << std::endl;
	}
	Window::~Window()
	{
		std::cout << "Closing The Window" << std::endl;
	}
	void Window::Update()
	{
		while (true)
		{

		}
	}
}