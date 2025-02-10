#include "pch.h"
#include "Shader.h"
#include <glad/glad.h>
#include "../Core/Core.h"
#include <glm/gtc/type_ptr.hpp>

namespace Palmy {
	constexpr const char* VERTEX_SHADER_TOKEN = "PALMY_VERTEX_SHADER";
	constexpr const char* FRAGMENT_SHADER_TOKEN = "PALMY_FRAGMENT_SHADER";

	Shader::Shader(const char* filepath)
	{
		std::string shaderSource = ReadShaderSource(filepath);
		const char* shaderSourceC = shaderSource.c_str();
		m_RendererId = glCreateShader(m_ShaderType);
		glShaderSource(m_RendererId, 1, &shaderSourceC, NULL);
		glCompileShader(m_RendererId);
		ValidateShader();
	}
	Shader::~Shader()
	{
		glDeleteShader(m_RendererId);
	}
	void Shader::ValidateShader() const
	{
		int success;
		glGetShaderiv(m_RendererId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char log[512];
			glGetShaderInfoLog(m_RendererId, 512, NULL, log);
			std::cout << log << std::endl;
		}
	}
	std::string Shader::ReadShaderSource(const char* filePath)
	{
		std::ifstream file(filePath);
		ENGINE_ASSERT(file.is_open(), "Unable to open file at {0}", filePath);
		std::stringstream ss;
		ss << file.rdbuf();
		std::string shaderSource = ss.str();

	
		if (shaderSource.find(VERTEX_SHADER_TOKEN) <= shaderSource.size())
		{
			m_ShaderType = GL_VERTEX_SHADER;
		}
		else if (shaderSource.find(FRAGMENT_SHADER_TOKEN) <= shaderSource.size())
		{
			m_ShaderType = GL_FRAGMENT_SHADER;
		}
		else {
			ENGINE_ASSERT("Unknown Shader type at {0}", filePath);
		}
		return shaderSource;
	}
	ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		Shader vertexShader(vertexShaderPath);
		Shader fragmentShader(fragmentShaderPath);
		m_RendererId = glCreateProgram();
		Bind();
		glAttachShader(m_RendererId, vertexShader.GetId());
		glAttachShader(m_RendererId, fragmentShader.GetId());
		glLinkProgram(m_RendererId);
		ValidateProgram();
		Unbind();
	}
	ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) 
	{
		m_RendererId = glCreateProgram();
		Bind();
		glAttachShader(m_RendererId, vertexShader.GetId());
		glAttachShader(m_RendererId, fragmentShader.GetId());
		glLinkProgram(m_RendererId);
		ValidateProgram();
		Unbind();
	}
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_RendererId);
	}
	void ShaderProgram::Bind() const
	{
		glUseProgram(m_RendererId);
	}
	void ShaderProgram::Unbind() const
	{
		glUseProgram(0);
	}
	void ShaderProgram::ValidateProgram() const
	{
		int success;
		glGetProgramiv(m_RendererId, GL_LINK_STATUS, &success);
		if (!success)
		{
			char log[512];
			glGetProgramInfoLog(m_RendererId, 512, NULL, log);
			std::cout << log << std::endl;
		}
	}
	uint32_t ShaderProgram::GetUniformLocation(const char* uniformName)const
	{
		return glGetUniformLocation(m_RendererId, uniformName);
	}
	void ShaderProgram::ChangeUniform(const char* uniformName, glm::vec2 value)
	{
		glUniform2f(GetUniformLocation(uniformName), value.x, value.y);
	}
	void ShaderProgram::ChangeUniform(const char* uniformName, glm::mat4 value)
	{
		glUniformMatrix4fv(GetUniformLocation(uniformName), 1, false, glm::value_ptr(value));
	}
}