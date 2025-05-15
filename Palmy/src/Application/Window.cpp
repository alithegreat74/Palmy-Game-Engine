#include "pch.h"
#include "Window.h"
#include "Core/Log.h"
#include "Core/Core.h"
#include "Input.h"
#include "ImGuiContext.h"
#include <imgui.h>
#include "../Core/Time.h"
#include <glm/glm.hpp>
#include "../Rendering/Renderer2D.h"
#include "../Rendering/RendererApi.h"
#include "ResourceManager.h"
#include "Core/RendererDebugger.h"

namespace Palmy {
	
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
		Window(info), m_Window(nullptr), 
		m_OrthographicCamera({0.0f,0.0f,1.0f},{0.0f,0.0f,-1.0f},-0.5f,0.5f,0.5f,-0.5f,0.1f,10.0f),
		m_CameraController(m_OrthographicCamera)
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
		ImGuiContext::Initialize(m_Window);
	}
	WindowsWindow::~WindowsWindow()
	{
		ImGuiContext::CleanUp();
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void WindowsWindow::Start()
	{
		m_Shader = std::make_shared<ShaderProgram>(*ResourceManager::GetShader(2204820834), *ResourceManager::GetShader(4187305228));
		m_Texture = ResourceManager::GetTexture2D(710627734);
		m_Renderer = std::make_unique<Renderer2D>();
	}
	void WindowsWindow::Update()
	{
		RendererApi::ClearColor(glm::vec4(0));
		ImGuiContext::BeginFrame();
		{
			ImGui::Begin("Statistics");
			ImGui::Text("Frame rate is: %f", (1/Timer::DeltaTime));
			ImGui::End();
		}
		m_Shader->Bind();
		m_Texture->Bind();
		m_Shader->ChangeUniform("uCameraMatrix", m_OrthographicCamera.GetCameraMatrix());
		//Testing 100 quad draws
		for (int i = -5; i < 6; i++)
		{
			for (int j = -5; j < 6; j++)
			{
				glm::vec4 color = (i * j) % 2 == 0 ? glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) : glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
				m_Renderer->RenderQuad(
					Transform2D(glm::vec2(((float)j)/10, ((float)i)/10), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.05, 0.05, 0.05)),color);
			}
		}
		m_Renderer->DrawBatch();
		m_Shader->Unbind();
		ImGuiContext::EndFrame();
		glfwPollEvents();
		RendererApi::SwapBuffers(m_Window);
	}
	bool WindowsWindow::OnWindowResize(const WindowResizedEvent& e)
	{
		ENGINE_LOG(e.ToString());
		return true;
	}
}