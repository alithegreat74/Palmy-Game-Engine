#pragma once
#include <glm/glm.hpp>
#include "../Math/Math.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>
#include <array>
#include "Buffers.h"

namespace Palmy {
	constexpr size_t BATCH_SIZE = 100;
	constexpr size_t QUAD_VERTEX_SIZE = 6;
	struct QuadVertexData
	{
	private:
		struct VertexData
		{
			glm::vec4 Position;
			glm::vec2 TextureCoordinates;
			glm::vec4 Color;
		};
	public:
		std::array<VertexData, QUAD_VERTEX_SIZE> VertexDatas;
		QuadVertexData();
	};
	class Renderer2D {
	public:
		Renderer2D();
		void RenderQuad(const Transform2D&);
		void RenderQuad(const Transform2D&, const glm::vec4 color);
		void DrawBatch();
	private:
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::vector<QuadVertexData> m_BatchData;
		size_t m_BatchIndex;
	};
}