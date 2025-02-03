#pragma once
#include <GLFW/glfw3.h>

namespace Palmy
{
	namespace ImGuiContext {
		void Initialize(GLFWwindow* window);
		void BeginFrame();
		void EndFrame();
		void CleanUp();
	}
}