#pragma once
#include <iostream>

namespace Palmy {
	struct WindowInfo
	{
		std::string Name;
		float Width, Height;

		WindowInfo(std::string name = "New Window", float width=1280.0f, float height=720.0f) :
			Name(name),Width(width),Height(height){}
	};
	class Window {
	public:
		Window(WindowInfo info = WindowInfo());
		~Window();

		void Update();
	private:
		WindowInfo m_WindowInfo;
	};
}