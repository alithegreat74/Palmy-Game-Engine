#pragma once

#include <glm/glm.hpp>
#include "../Math/Math.h"
#include "Texture.h"
#include "Shader.h"

namespace Palmy {
	class Renderer2D {
	public:
		static void RenderQuad(const Transform2D&, const ShaderProgram& program, const Texture& texture);
		static void RenderQuad(const Transform2D&, const ShaderProgram& program, const glm::vec4 color);
	};
}