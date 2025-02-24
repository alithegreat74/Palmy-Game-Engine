#include "pch.h"
#include "RendererApi.h"
#include "../Core/Core.h"

namespace Palmy 
{
	void RendererApi::ClearColor(glm::vec4 color)
	{
		glClearColor(color.x, color.y, color.z, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void RendererApi::SetRendererFlags()
	{

	}
	void RendererApi::SwapBuffers(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}
	void RendererApi::QuadDrawCall()
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}