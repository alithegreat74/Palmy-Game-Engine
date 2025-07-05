#include "Bird.h"

namespace Sandbox {
	Bird::Bird(std::shared_ptr<Palmy::Texture2D> texture, float speedDecline, bool fitScreen)
		:Palmy::Renderable(texture, fitScreen), m_SpeedDecline(speedDecline), m_VerticalSpeed(0)
	{}
	Bird::Bird(std::shared_ptr<Palmy::Texture2D> texture, float speedDecline, bool fitScreen, Palmy::Transform2D transform)
		:Palmy::Renderable(texture, fitScreen), m_SpeedDecline(speedDecline), m_VerticalSpeed(0)
	{
		m_Transform = transform;
	}
	Palmy::RenderableData Bird::GetRenderableData()
	{
		m_Transform.Position += glm::vec2(0, m_VerticalSpeed)* (float)Palmy::Time::s_DeltaTime;
		m_VerticalSpeed -= m_SpeedDecline;
		return Palmy::Renderable::GetRenderableData();
	}
	void Bird::SetVerticalSpeed(float speed)
	{
		m_VerticalSpeed = speed;
	}
}