#pragma once
#include <glm.hpp>

namespace Palmy {
	class Shader {
	public:
		Shader(const char* filepath, uint32_t shaderTyp);
		~Shader();
		void ValidateShader()const;
		inline uint32_t GetId()const { return m_RendererId; }
	private:
		std::string ReadShaderSource(const char* filePath)const;
	private:
		uint32_t m_RendererId;
	};

	class ShaderProgram {
	public:
		ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
		~ShaderProgram();
		void Bind()const;
		void Unbind()const;
		void ValidateProgram()const;
		inline uint32_t GetUniformLocation(const char* uniformName)const;
		void ChangeUniform(const char* uniformName, glm::vec2 value);
	private:
		uint32_t m_RendererId;
	};
}