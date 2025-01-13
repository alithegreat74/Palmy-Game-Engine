#pragma once
#include <memory>
#include <iostream>
#include <GLFW/glfw3.h>
#include "../Event/WindowEvent.h"
#include "../Event/MouseEvent.h"
#include "../Event/KeyEvent.h"

namespace Palmy {

	using EventCallbackFunction = std::function<void(Event&)>;

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
		virtual void SetEventCallback(const EventCallbackFunction& callbackFunction) = 0;
		static std::unique_ptr<Window>Create(const WindowInfo& info = WindowInfo());
		virtual void Update() = 0;
		virtual bool ShouldWindowClose() = 0;
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
		virtual void SetEventCallback(const EventCallbackFunction& callbackFunction)override { m_WindowData.CallbackFunction = callbackFunction; }
		virtual void Update()override;
		static bool OnWindowResize(const WindowResizedEvent& e);
		virtual bool ShouldWindowClose() { return !glfwWindowShouldClose(m_Window); }
	private:
		struct WindowData
		{
			float Width, Height;
			std::string Name;
			EventCallbackFunction CallbackFunction;
		};
		WindowData m_WindowData;
		GLFWwindow* m_Window;
	};
}