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
		Window(info), m_Window(nullptr)
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
		m_Texture = ResourceManager::GetTexture2D(1153661826);
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
		m_Renderer->StartDraw();
		m_Renderer->RenderQuad(Transform2D(), m_Texture, { {0.0f,384.0f},{128.0f,128.0f} });
		m_Renderer->DrawBatch();
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