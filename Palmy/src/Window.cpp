#include "Window.h"
#include "Log.h"

namespace Palmy {
	Window::Window(WindowInfo info):
		m_WindowInfo(info)
	{
		ENGINE_LOG("Creating A Window");
	}
	Window::~Window()
	{
		ENGINE_LOG("Closing The Window");
	}
	void Window::Update()
	{
		while (true)
		{

		}
	}
}