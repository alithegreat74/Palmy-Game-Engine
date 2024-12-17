#pragma once
#include <memory>
#include <iostream>
#include <GLFW/glfw3.h>

namespace Palmy {
	struct WindowInfo
	{
		std::string Name;
		float Width, Height;

		WindowInfo(std::string name = "New Window", float width = 1280.0f, float height = 720.0f) :
			Name(name), Width(width), Height(height)
		{
			Name == "" ? Name = "New Window" : Name = Name;
		}
	};

	class Window {
	public:
		Window(const WindowInfo& info);
		virtual ~Window();
		static std::unique_ptr<Window>Create(const WindowInfo& info = WindowInfo());
		virtual void Update() = 0;
	protected:
		WindowInfo m_WindowInfo;
	};

	/// <summary>
	/// The Windows window will use glfw as it's main windowing library not sure what to use for other operating systems
	/// </summary>
	class WindowsWindow :public Window {
	public:
		WindowsWindow(const WindowInfo& info);
		~WindowsWindow()override;
		virtual void Update()override;
	private:
		GLFWwindow* m_Window;
	};
}