#include "pch.h"
#include "RendererDebugger.h"

#ifdef DEBUG
namespace Palmy
{
	RendererDebugger::RendererDebugger(const std::string& functionName)
		:m_FunctionName(functionName)
	{
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
			ENGINE_ERROR("A graphics api error occurred before {0} ErrorCode:{1:#x}", m_FunctionName, error);
	}
	RendererDebugger::~RendererDebugger()
	{
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
			ENGINE_ERROR("A graphics api error occurred at {0} ErrorCode:{1:#x}", m_FunctionName, error);
	}
}
#endif // DEBUG

