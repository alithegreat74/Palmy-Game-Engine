#include "pch.h"
#include "Input.h"
#include "Core/Core.h"
#include <GLFW/glfw3.h>
#include "../Core/Time.h"

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
}