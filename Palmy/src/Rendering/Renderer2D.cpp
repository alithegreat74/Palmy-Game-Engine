#include "pch.h"
#include "Renderer2D.h"
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RendererApi.h"

namespace Palmy {
	void Renderer2D::RenderQuad(const Transform2D& transform, const ShaderProgram& program, const Texture& texture) {
		glm::mat4 mat(1.0);
		mat = glm::translate(mat, glm::vec3(transform.Position, 0.0));
		if (glm::length(transform.Rotation) > 0)
			mat = glm::rotate(mat, glm::radians(glm::length(transform.Rotation)), glm::normalize(transform.Rotation));
		mat = glm::scale(mat, transform.Scale);
		program.ChangeUniform("uTransform", mat);
		program.ChangeUniform("uColor", glm::vec4(1.0, 1.0, 1.0, 1.0));
		texture.Bind();
		RendererApi::QuadDrawCall();
	}

	void Renderer2D::RenderQuad(const Transform2D& transform, const ShaderProgram& program, const glm::vec4 color)
	{
		glm::mat4 mat(1.0);
		mat = glm::translate(mat, glm::vec3(transform.Position, 0.0));
		mat = glm::rotate(mat, glm::length(transform.Rotation), glm::normalize(transform.Rotation));
		mat = glm::scale(mat, transform.Scale);
		program.ChangeUniform("uTransform", mat);
		program.ChangeUniform("uColor", color);
		RendererApi::QuadDrawCall();
	}
}