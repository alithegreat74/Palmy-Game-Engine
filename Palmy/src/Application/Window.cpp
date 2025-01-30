#include "pch.h"
#include "Window.h"
#include "Core/Log.h"
#include "Core/Core.h"
#include "Input.h"



namespace Palmy {
	constexpr float VERTICIES[] = {
		-0.5f,-0.5f, 0.0f, 0.0f,
		 0.5f,-0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, 1.0f, 1.0f,
		 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f,-0.5f, 0.0f, 0.0f,

	};
	Window::Window(const WindowInfo& info):
		m_WindowInfo(info)
	{
		ENGINE_LOG("Creating a window called {0}", info.Name);
	}
	Window::~Window()
	{
	}
	std::unique_ptr<Window> Window::Create(const WindowInfo& info)
	{
#ifdef WINDOWS
		return std::make_unique<WindowsWindow>(info);
#else
#error Palmy Only Supports Windows 
#endif // WINDOWS
	}

	WindowsWindow::WindowsWindow(const WindowInfo& info):
		Window(info),m_Window(nullptr)
	{
		ENGINE_ASSERT(glfwInit(), "Failed to initialize glfw");
		m_Window = glfwCreateWindow(info.Width, info.Height, info.Name.c_str(), NULL, NULL);
		m_WindowData.Width = info.Width;
		m_WindowData.Height = info.Height;
		m_WindowData.Name = info.Name;
		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		glfwMakeContextCurrent(m_Window);
		ENGINE_ASSERT(gladLoadGL(), "Failed to initialize opengl functinos");

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowResizedEvent e{(float)width, (float)height};
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->CallbackFunction(e);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS)
			{
				KeyPressedEvent e(key);
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data->CallbackFunction(e);
			}
			else if (action == GLFW_RELEASE)
			{
				KeyReleasedEvent e(key);
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data->CallbackFunction(e);
			}
			});
		Input::Init(m_Window);
		m_Shader = std::make_shared<ShaderProgram>("Assets/Shaders/QuadVertexShader.glsl", "Assets/Shaders/QuadFragmentShader.glsl");
		m_Texture = std::make_shared<Texture2D>("Assets/Textures/Hardwood Floor.jpg");
		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->Bind();
		VertexBuffer vbo(VERTICIES, sizeof(VERTICIES), { { GL_FLOAT,2,2 * sizeof(float),false },{GL_FLOAT,2,2*sizeof(float),false}});
		vbo.Unbind();
		m_VertexArray->Unbind();
	}
	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		
	}
	void WindowsWindow::Update()
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		m_Shader->Bind();
		m_VertexArray->Bind();
		m_Texture->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_Texture->Unbind();
		m_VertexArray->Unbind();
		m_Shader->Unbind();
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	bool WindowsWindow::OnWindowResize(const WindowResizedEvent& e)
	{
		ENGINE_LOG(e.ToString());
		return true;
	}
}