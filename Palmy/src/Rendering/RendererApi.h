#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Palmy {
	class RendererApi {
	public:
		static void ClearColor(glm::vec4 color);
		static void SetRendererFlags();
		static void SwapBuffers(GLFWwindow* window);
		static void QuadDrawCall(size_t vertexSize);
	};
}