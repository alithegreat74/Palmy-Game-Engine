#pragma once 
#include <Palmy.h>

namespace Sandbox
{
	class Bird :public Palmy::Renderable
	{
	public:
		Bird(std::shared_ptr<Palmy::Texture2D> texture, float speedDecline, bool fitScreen);
		Bird(std::shared_ptr<Palmy::Texture2D> texture, float speedDecline, bool fitScreen, Palmy::Transform2D transform);
		virtual Palmy::RenderableData GetRenderableData() override;
		void SetVerticalSpeed(float speed);
		inline const glm::vec2& GetPosition()const {
			return m_Transform.Position;
		}
	private:
		float m_VerticalSpeed;
		float m_SpeedDecline;
	};
}