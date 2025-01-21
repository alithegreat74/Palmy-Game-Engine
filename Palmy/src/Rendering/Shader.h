#pragma once

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
		ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
		~ShaderProgram();
		void Bind()const;
		void Unbind()const;
		void ValidateProgram()const;

	private:
		uint32_t m_RendererId;
	};
}