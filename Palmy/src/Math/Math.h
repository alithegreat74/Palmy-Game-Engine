#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Palmy {
	struct Transform2D
	{
		glm::vec2 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
		Transform2D(glm::vec2 position, glm::vec3 rotation, glm::vec3 scale) 
			:Position(position),Rotation(rotation),Scale(scale)
		{}
		Transform2D(glm::vec2 position)
			:Position(position), Rotation({0.0,0.0,0.0}), Scale({1.0,1.0,1.0})
		{}
		Transform2D()
			:Position({0.0,0.0}), Rotation({0.0,0.0,0.0}), Scale({1.0,1.0,1.0})
		{}
		const glm::mat4 GetTransformMatrix()const
		{
			glm::mat4 transformMatrix(1.0);
			transformMatrix = glm::translate(transformMatrix, glm::vec3(Position, 0.0));
			if (glm::length(Rotation) > 0)
				transformMatrix = glm::rotate(transformMatrix, glm::radians(glm::length(Rotation)), glm::normalize(Rotation));
			transformMatrix = glm::scale(transformMatrix, Scale);
			return transformMatrix;
		}
	};
}