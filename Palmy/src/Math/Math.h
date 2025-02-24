#pragma once
#include <glm/glm.hpp>
namespace Palmy {
	struct Transform2D
	{
		glm::vec2 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
		Transform2D(glm::vec2 position = { 0.0,0.0 }, glm::vec3 rotation = { 0.0, 0.0, 0.0 }, glm::vec3 scale = { 1.0,1.0,1.0 }) 
			:Position(position),Rotation(rotation),Scale(scale)
		{}
	};
}