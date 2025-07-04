#pragma once
#include <Palmy.h>

namespace Sandbox {
	class Background : public Palmy::Renderable
	{
	public:
		Background(std::shared_ptr<Palmy::Texture2D> texture, float backgroundSpeed, bool fitScreen)
			:Palmy::Renderable(texture, fitScreen), m_BackgroundSpeed(backgroundSpeed)
		{}
		Background(std::shared_ptr<Palmy::Texture2D> texture, float backgroundSpeed, bool fitScreen, Palmy::Transform2D transform)
			:Palmy::Renderable(texture, fitScreen), m_BackgroundSpeed(backgroundSpeed)
		{
			m_Transform = transform;
		}
		virtual Palmy::RenderableData GetRenderableData()override {
			if (m_Transform.Position.x + m_BackgroundSpeed * (float)Palmy::Time::s_DeltaTime >= 2.0)
				m_Transform.Position = { -2.0,0.0 };

			m_Transform.Position += glm::vec2(m_BackgroundSpeed * (float)Palmy::Time::s_DeltaTime,0.0f);
			return Palmy::Renderable::GetRenderableData();
		}
	private:
		float m_BackgroundSpeed;
	};
}