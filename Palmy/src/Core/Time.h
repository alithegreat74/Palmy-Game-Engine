#pragma once
#include <GLFW/glfw3.h>
namespace Palmy {
	class Timer {
	public:
		Timer() = delete;
		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;
		static void Calculate() {
			Time = glfwGetTime();
			DeltaTime = Time - s_PreviousTime;
			s_PreviousTime = Time;
		}
	public:
		inline static double Time = 0;
		inline static double DeltaTime = 0;
	private:
		inline static double s_PreviousTime = 0;
	};
}