#include "PipeGenerator.h"

namespace Sandbox {
	constexpr float SPACE_BETWEEN_PIPES = 1.0f;
	constexpr float PIPE_WIDTH = 0.173437506f;
	constexpr float PIPE_NORMAL_HEIGHT = 1.186111092f/2;
	PipeGenerator::PipeGenerator(std::shared_ptr<Palmy::Texture2D> texture, float pipeMoveSpeed)
		:m_Texture(texture), m_PipeMoveSpeed(pipeMoveSpeed)
	{
		m_PipeTransforms = std::array<Palmy::Transform2D, s_NumberOfPipes>{
			Palmy::Transform2D(glm::vec2(-SPACE_BETWEEN_PIPES * 1, -0.65f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 1.0f)),
			Palmy::Transform2D(glm::vec2(-SPACE_BETWEEN_PIPES * 1,  0.65f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 1.0f)),
			Palmy::Transform2D(glm::vec2(-SPACE_BETWEEN_PIPES * 2, -0.85f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.3f, 1.0f)),
			Palmy::Transform2D(glm::vec2(-SPACE_BETWEEN_PIPES * 2,  0.585f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.1f, 1.0f)),
			Palmy::Transform2D(glm::vec2(-SPACE_BETWEEN_PIPES * 3, -0.585f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.1f, 1.0f)),
			Palmy::Transform2D(glm::vec2(-SPACE_BETWEEN_PIPES * 3,  0.85f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.3f, 1.0f)),
			Palmy::Transform2D(glm::vec2(-SPACE_BETWEEN_PIPES * 4, -0.77f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.4f, 1.0f)),
			Palmy::Transform2D(glm::vec2(-SPACE_BETWEEN_PIPES * 4,  0.585f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
		};
	}
	const std::array<Palmy::RenderableData, 8> PipeGenerator::GetRenderableData()
	{
		for (size_t i = 0; i < s_NumberOfPipes; i++)
		{
			m_PipeTransforms[i].Position += glm::vec2(m_PipeMoveSpeed * Palmy::Time::s_DeltaTime, 0.0f);
			if (m_PipeTransforms[i].Position.x >= 1.0f)
			{
				m_PipeTransforms[i].Position = glm::vec2(-1.5f, m_PipeTransforms[i].Position.y);
			}
		}
		return std::array<Palmy::RenderableData, s_NumberOfPipes>{
			Palmy::RenderableData(m_Texture, m_PipeTransforms[0], Palmy::SubTextureInfo(), false),
			Palmy::RenderableData(m_Texture, m_PipeTransforms[1], Palmy::SubTextureInfo(), false),
			Palmy::RenderableData(m_Texture, m_PipeTransforms[2], Palmy::SubTextureInfo(), false),
			Palmy::RenderableData(m_Texture, m_PipeTransforms[3], Palmy::SubTextureInfo(), false),
			Palmy::RenderableData(m_Texture, m_PipeTransforms[4], Palmy::SubTextureInfo(), false),
			Palmy::RenderableData(m_Texture, m_PipeTransforms[5], Palmy::SubTextureInfo(), false),
			Palmy::RenderableData(m_Texture, m_PipeTransforms[6], Palmy::SubTextureInfo(), false),
			Palmy::RenderableData(m_Texture, m_PipeTransforms[7], Palmy::SubTextureInfo(), false),
		};
	}
	bool PipeGenerator::CheckForCollision(const glm::vec2& position)
	{
		for (size_t i = 0; i < s_NumberOfPipes; i+=2)
		{
			if (abs(m_PipeTransforms[i].Position.x - position.x) > PIPE_WIDTH / 2)
				continue;
 			float bottomPipeTop = m_PipeTransforms[i].Position.y + PIPE_NORMAL_HEIGHT * m_PipeTransforms[i].Scale.y;
			float topPipeBottom = m_PipeTransforms[i + 1].Position.y - PIPE_NORMAL_HEIGHT * m_PipeTransforms[i + 1].Scale.y;
			if (bottomPipeTop > position.y || topPipeBottom < position.y)
				return true;
		}
		return false;
	}
}