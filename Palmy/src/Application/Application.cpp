#include "pch.h"
#include "Application.h"
#include "../Core/Core.h"
#include "Input.h"
#include "../Core/Time.h"
#include "ImGuiContext.h"
#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Palmy {
	Application::Application(const std::string& applicationName, float width, float height)
	{
		m_Window = Window::Create(WindowInfo(applicationName, width, height));
		m_Window->SetEventCallback(ENGINE_BIND(Application::OnEvent));
		m_LayerStack = std::make_unique<LayerStack>();
		m_ResourceManager = std::make_unique<ResourceManager>();
		ResourceManager::CheckForResources();
		ImGuiContext::Initialize(static_cast<GLFWwindow*>(m_Window->GetWindowContext()));
		m_Renderer = std::make_shared<Renderer2D>(width, height);
	}
    void Application::Run()
    {
		while (m_Window->ShouldWindowClose())
		{
			ResourceManager::CheckForResources();
			m_Window->BeginFrame();
			m_Renderer->StartDraw();
			ImGuiContext::BeginFrame();
			Time::Calculate();
			for (auto it = m_LayerStack->rbegin(); it < m_LayerStack->rend(); it++) {
				auto layer = *it;
				layer->OnUpdate();
			}
			{
				ImGui::Begin("Statistics");
				ImGui::Text("Frame rate is: %f", (1 / Time::s_DeltaTime));
				ImGui::End();
			}
			m_Renderer->DrawBatch();
			ImGuiContext::EndFrame();
			m_Window->EndFrame();
		}
	}

	void Application::OnEvent(Event& e)
	{
		for (auto it = m_LayerStack->rbegin(); it < m_LayerStack->rend(); it++) {
			auto layer = *it;
			layer->OnEvent(e);
		}
	}

	void Application::AttachLayer(std::shared_ptr<Layer> layer)
	{
		m_LayerStack->AttachLayer(layer);
		layer->OnAttach(m_Renderer);
	}
	
}

