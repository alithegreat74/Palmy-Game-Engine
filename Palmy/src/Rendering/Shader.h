#pragma once
#include <glm.hpp>

namespace Palmy {
	class Shader {
	public:
		Shader(const char* filepath);
		~Shader();
		void ValidateShader()const;
		inline uint32_t GetId()const { return m_RendererId; }
	private:
		std::string ReadShaderSource(const char* filePath);
	private:
		uint32_t m_RendererId;
		uint32_t m_ShaderType;
	};

	class ShaderProgram {
	public:
		ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
		ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
		~ShaderProgram();
		void Bind()const;
		void Unbind()const;
		void ValidateProgram()const;
		inline uint32_t GetUniformLocation(const char* uniformName)const;
		void ChangeUniform(const char* uniformName, glm::vec2 value);
		void ChangeUniform(const char* uniformName, glm::mat4 value);
	private:
		uint32_t m_RendererId;
	};
}