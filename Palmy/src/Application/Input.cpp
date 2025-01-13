#include "pch.h"
#include "Input.h"
#include "Core/Core.h"
#include <GLFW/glfw3.h>

namespace Palmy
{
	void Input::Init(void* window)
	{
		s_Window = window;
	}
	bool Input::GetKeyDown(KeyCode keyCode)
	{
		int state = glfwGetKey(static_cast<GLFWwindow*>(s_Window), keyCode);
		return state == GLFW_PRESS;
	}
	bool Input::GetKeyUp(KeyCode keyCode)
	{
		int state = glfwGetKey(static_cast<GLFWwindow*>(s_Window), keyCode);
		return state == GLFW_RELEASE;
	}

	bool Input::GetMouseButtonDown(KeyCode buttonCode)
	{
		int state = glfwGetMouseButton(static_cast<GLFWwindow*>(s_Window), buttonCode);
		return state == GLFW_PRESS;
	}

	bool Input::GetMouseButtonUp(KeyCode buttonCode)
	{
		int state = glfwGetMouseButton(static_cast<GLFWwindow*>(s_Window), buttonCode);
		return state == GLFW_RELEASE;
	}
	//TODO: Create a way for user the get the mouse delta
	glm::vec2 Input::GetMousePosition()
	{
		double xPos, yPos;
		glfwGetCursorPos(static_cast<GLFWwindow*>(s_Window), &xPos, &yPos);
		return glm::vec2({ xPos,yPos });
	}
	
}