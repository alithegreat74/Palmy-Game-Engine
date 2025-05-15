#include "pch.h"
#include "Renderer2D.h"
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RendererApi.h"

namespace Palmy {
	void Renderer2D::RenderQuad(const Transform2D& transform, const ShaderProgram& program, const Texture& texture) {
		glm::mat4 transfromMatrix = transform.GetTransformMatrix();
		program.ChangeUniform("uTransform", transfromMatrix);
		program.ChangeUniform("uColor", glm::vec4(1.0, 1.0, 1.0, 1.0));
		texture.Bind();
		RendererApi::QuadDrawCall();
	}

	void Renderer2D::RenderQuad(const Transform2D& transform, const ShaderProgram& program, const glm::vec4 color)
	{
		glm::mat4 transformMatrix = transform.GetTransformMatrix();
		program.ChangeUniform("uTransform", transformMatrix);
		program.ChangeUniform("uColor", color);
		RendererApi::QuadDrawCall();
	}
}