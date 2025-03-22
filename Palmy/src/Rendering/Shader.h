#pragma once
#include <glm.hpp>

namespace Palmy {
	class Shader {
	public:
		Shader(const char* filepath, uint32_t shaderType, uint32_t resourceId);
		~Shader();
		void ValidateShader()const;
		inline uint32_t GetId()const { return m_RendererId; }
	private:
		std::string ReadShaderSource(const char* filePath)const;
	private:
		uint32_t m_RendererId;
		uint32_t m_ResourceId;
	};

	class ShaderProgram {
	public:
		ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
		~ShaderProgram();
		void Bind()const;
		void Unbind()const;
		void ValidateProgram()const;
		inline uint32_t GetUniformLocation(const char* uniformName)const;
		void ChangeUniform(const char* uniformName, glm::vec2 value)const;
		void ChangeUniform(const char* uniformName, glm::mat4 value)const;
		void ChangeUniform(const char* uniformName, glm::vec4 value)const;
	private:
		uint32_t m_RendererId;
	};
}