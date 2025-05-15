#pragma once

#include <glm/glm.hpp>
#include "../Math/Math.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>
#include <array>

namespace Palmy {
	constexpr size_t BATCH_SIZE = 100;
	constexpr size_t QUAD_VERTEX_SIZE = 6;
	struct QuadVertexData
	{
		std::array<glm::vec4, QUAD_VERTEX_SIZE> Positions;
		std::array<glm::vec2, QUAD_VERTEX_SIZE> TexCoordinates;
	};
	class Renderer2D {
	public:
		Renderer2D();
		void RenderQuad(const Transform2D&, const ShaderProgram& program, const Texture& texture);
		void RenderQuad(const Transform2D&, const ShaderProgram& program, const glm::vec4 color);
	private:
	};
}