#include "pch.h"
#include "Window.h"
#include "Core/Log.h"
#include "Core/Core.h"
#include "Input.h"



namespace Palmy {
	//TODO: read shaders from a seperate file
	constexpr const char* DEFAULT_VERTEX_SHADER =
		R"(#version 330 core
			layout (location = 0) in vec2 aPos;
			void main()
			{
				gl_Position = vec4(aPos,0.0, 1.0);
			})";
	constexpr const char* DEFAULT_FRAGMENT_SHADER =
		R"(#version 330 core
			out vec4 FragColor;
			void main()
			{
				FragColor = vec4(0.8,0.2,0.4,1.0);
			}
			)";

	constexpr float VERTICIES[] = {
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.0f, 0.5f
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


		//TODO: Handle Shader loading in an seperate class
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &DEFAULT_VERTEX_SHADER, NULL);
		glCompileShader(vertexShader);
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &DEFAULT_FRAGMENT_SHADER, NULL);
		glCompileShader(fragmentShader);
		m_Shader = glCreateProgram();
		glAttachShader(m_Shader, vertexShader);
		glAttachShader(m_Shader, fragmentShader);
		glLinkProgram(m_Shader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		//TODO: Handle Vertex Buffer and Vertex Array and Index Buffer in a seperate class
		glCreateVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		uint32_t vbo;
		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICIES), VERTICIES, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

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
		glUseProgram(m_Shader);
		glBindVertexArray(m_VertexArray);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	bool WindowsWindow::OnWindowResize(const WindowResizedEvent& e)
	{
		ENGINE_LOG(e.ToString());
		return true;
	}
}