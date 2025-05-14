#pragma once

namespace Palmy
{
#ifdef DEBUG
#include <glad/glad.h>
	class RendererDebugger
	{
	public:
		RendererDebugger(const std::string& functionName);
		~RendererDebugger();
	private:
		std::string m_FunctionName;
	};
#define CHECK_FOR_GRAPHICS_ERRORS RendererDebugger rd(__FUNCTION__)

#endif 

}