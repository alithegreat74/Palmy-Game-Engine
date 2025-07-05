#pragma once
#include <GLFW/glfw3.h>
namespace Palmy {
	class Time {
	public:
		Time() = delete;
		Time(const Time&) = delete;
		Time(Time&&) = delete;
		static void Calculate() {
			s_Time = glfwGetTime();
			s_DeltaTime = s_Time - s_PreviousTime;
			s_PreviousTime = s_Time;
		}
	public:
		inline static double s_Time = 0;
		inline static double s_DeltaTime = 0;
	private:
		inline static double s_PreviousTime = 0;
	};
}