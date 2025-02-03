#include "pch.h"
#include "Application.h"
#include "../Core/Core.h"
#include "Input.h"
#include "../Core/Time.h"
#include "ImGuiContext.h"
#include <imgui.h>

namespace Palmy {
	Application::Application(const std::string& applicationName)
	{
		m_Window = Window::Create(WindowInfo("Application Window", 1280.0f, 720.0f));
		m_Window->SetEventCallback(ENGINE_BIND(Application::OnEvent));
		m_LayerStack = std::make_unique<LayerStack>();
	}
    void Application::Run()
    {
		while (m_Window->ShouldWindowClose())
		{
			m_Window->Update();
			Timer::Calculate();
			ENGINE_LOG("Time:{0},DeltaTime:{1}", Timer::Time, Timer::DeltaTime);
			for (auto it = m_LayerStack->rbegin(); it < m_LayerStack->rend(); it++) {
				auto layer = *it;
				layer->OnUpdate();
			}
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
		layer->OnAttach();
	}
	
}

