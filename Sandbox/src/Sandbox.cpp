#include <memory>
#include "Palmy.h"
#include <./src/Core/EntryPoint.h>
#include <Palmy.h>
#include <fstream>
#include "Background.h"
#include "./Bird.h"
#include "./PipeManager.h"

namespace Sandbox {

	constexpr float BIRD_FLAP_SPEED = 2.0f;
	constexpr float BIRD_SPEED_DECLINE = 0.1f;
	float g_BackgroundSpeed = 1.0f;
	float PIPE_SPEED = 0.8f;

	constexpr uint32_t TEXTURE_ID_BACKGROUND = 1589568186;
	constexpr uint32_t TEXTURE_ID_BIRD = 3123682840;
	constexpr uint32_t TEXTURE_ID_PIPE = 3837834200;
	constexpr uint32_t TEXTURE_ID_GAME_FINISHED = 985712114;

	class ExampleLayer :public Palmy::Layer {
	public:
		ExampleLayer(const std::string& layerName = "New Layer"):
			Palmy::Layer(layerName)
		{
			std::shared_ptr<Palmy::Texture2D> backgroundTexture = Palmy::ResourceManager::GetTexture2D(TEXTURE_ID_BACKGROUND);
			std::shared_ptr<Palmy::Texture2D> birdTexture = Palmy::ResourceManager::GetTexture2D(TEXTURE_ID_BIRD);
			std::shared_ptr<Palmy::Texture2D> pipeTexture = Palmy::ResourceManager::GetTexture2D(TEXTURE_ID_PIPE);
			m_GameFinishedTexture = Palmy::ResourceManager::GetTexture2D(TEXTURE_ID_GAME_FINISHED);
			m_PipeManager = std::make_unique<PipeManager>(pipeTexture, PIPE_SPEED);
			m_BackgroundLeft = std::make_unique<Background>(backgroundTexture, g_BackgroundSpeed, true);
			m_BackgroundRight = std::make_unique<Background>(backgroundTexture, g_BackgroundSpeed, true, Palmy::Transform2D(glm::vec2(-2.0, 0.0)));
			m_Bird = std::make_unique<Bird>(birdTexture, BIRD_SPEED_DECLINE, false, Palmy::Transform2D(glm::vec2(0.5f,-0.5f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.25f)));
		}
		~ExampleLayer(){}

		virtual void OnUpdate() {
			if (m_PipeManager->CheckForCollision(m_Bird->GetPosition()))
			{
				m_Renderer->RenderQuad(Palmy::Transform2D(), m_GameFinishedTexture, false);
				return;
			}
			m_Renderer->RenderQuad(m_BackgroundLeft->GetRenderableData());
			m_Renderer->RenderQuad(m_BackgroundRight->GetRenderableData());
			m_Renderer->RenderQuad(m_Bird->GetRenderableData());
			m_PipeManager->UpdatePipes();
			const std::array<Palmy::RenderableData, PipeManager::s_NumberOfPipes> pipesData = m_PipeManager->GetRenderableData();
			for (auto pipe : pipesData)
			{
				m_Renderer->RenderQuad(pipe);
			}
		}
		virtual void OnEvent(Palmy::Event& event)override {
			Palmy::EventHandler::Handle<Palmy::KeyPressedEvent>(ENGINE_BIND(ExampleLayer::KeyWasPressed), event);
		}
		bool KeyWasPressed(const Palmy::KeyPressedEvent& event)
		{
			if (event.GetKey() != Palmy::KeyCode::KEY_SPACE)
				return true;

			m_Bird->SetVerticalSpeed(BIRD_FLAP_SPEED);
			return true;
		}

	private:
		std::unique_ptr<Background> m_BackgroundLeft;
		std::unique_ptr<Background> m_BackgroundRight;
		std::unique_ptr<Bird> m_Bird;
		std::unique_ptr<PipeManager> m_PipeManager;
		std::shared_ptr<Palmy::Texture2D> m_GameFinishedTexture;
	};

	class SandboxApp :public Palmy::Application {
	public:
		SandboxApp() :
			Palmy::Application("Sandbox")
		{
			AttachLayer(std::make_shared<ExampleLayer>("Example Layer"));
		}
	};
}



Palmy::Application* Palmy::Create() {

	return new Sandbox::SandboxApp();
}

