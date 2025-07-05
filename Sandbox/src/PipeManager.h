#include <Palmy.h>
#include <array>

namespace Sandbox {
	class PipeManager {
	public:
		static constexpr int s_NumberOfPipes = 8;
	public:
		PipeManager(std::shared_ptr<Palmy::Texture2D> texture, float pipeMoveSpeed);
		const std::array<Palmy::RenderableData, s_NumberOfPipes> GetRenderableData();
		void UpdatePipes();
		bool CheckForCollision(const glm::vec2& position);
	private:
		std::array<Palmy::Transform2D, s_NumberOfPipes> m_PipeTransforms;
		std::shared_ptr<Palmy::Texture2D> m_Texture;
		float m_PipeMoveSpeed;
	};
}