#include "pch.h"
#include "ResourceLoader.h"
#include <yaml-cpp/yaml.h>
#include "../Core/Core.h"
#include <glad/glad.h>
#include <filesystem>

namespace Palmy
{
	std::shared_ptr<Texture2D> ResourceLoader::LoadTexture(const char* filepath)
	{
		std::string metapath(filepath);
		metapath += ".meta";
		YAML::Node metadata = YAML::LoadFile(metapath);
		ENGINE_ASSERT((metadata["Type"].as<std::string>() == "Texture"), "{0} is not a texture", filepath);
		return std::make_shared<Texture2D>(filepath, metadata["Id"].as<uint32_t>());
	}
	std::shared_ptr<Shader> ResourceLoader::LoadShader(const char* filepath)
	{
		std::string metapath(filepath);
		metapath += ".meta";
		YAML::Node metadata = YAML::LoadFile(metapath);
		ENGINE_ASSERT((metadata["Type"].as<std::string>() == "Shader"), "{0} is not a shader", filepath);
		uint32_t shaderType = 0;
		std::string shaderTypeMeta = metadata["ShaderType"].as<std::string>();
		if (shaderTypeMeta == "Vertex")
			shaderType = GL_VERTEX_SHADER;
		else if (shaderTypeMeta == "Fragment")
			shaderType = GL_FRAGMENT_SHADER;
		return std::make_shared<Shader>(filepath, shaderType, metadata["Id"].as<uint32_t>());
	}
	ResourceMetaData ResourceLoader::GetResourceType(const char* filepath)
	{
		std::string metapath(filepath);
		metapath += ".meta";
		YAML::Node metadata = YAML::LoadFile(metapath);

		return { metadata["Type"].as<std::string>(),metadata["Id"].as<uint32_t>() };
	}
}