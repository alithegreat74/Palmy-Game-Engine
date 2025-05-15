#pragma once
#include <memory>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Event/WindowEvent.h"
#include "../Event/MouseEvent.h"
#include "../Event/KeyEvent.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Buffers.h"
#include "../Rendering/Texture.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Renderer2D.h"

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
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual bool ShouldWindowClose() = 0;
		virtual void* GetWindowContext() = 0;
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
		virtual void Start()override;
		virtual void Update()override;
		static bool OnWindowResize(const WindowResizedEvent& e);
		virtual bool ShouldWindowClose() { return !glfwWindowShouldClose(m_Window); }
		virtual void* GetWindowContext()override{return m_Window;}
	private:
		struct WindowData
		{
			float Width, Height;
			std::string Name;
			EventCallbackFunction CallbackFunction;
		};
		WindowData m_WindowData;
		GLFWwindow* m_Window;
		std::shared_ptr<ShaderProgram> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Texture2D> m_Texture;
		std::unique_ptr<Renderer2D> m_Renderer;
		OrthoGraphicCamera m_OrthographicCamera;
		CameraController m_CameraController;
	};
}