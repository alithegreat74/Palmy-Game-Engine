#include "pch.h"
#include "ResourceLoader.h"
#include <yaml-cpp/yaml.h>
#include "../Core/Core.h"

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
		return std::make_shared<Shader>(filepath, metadata["Id"].as<uint32_t>());
	}
}