#pragma once
#include "../Rendering/Texture.h"
#include "../Rendering/Shader.h"
#include <memory>
#include <filesystem>

namespace Palmy
{
	struct ResourceMetaData
	{
		std::string Type;
		uint32_t Id;
	};
	class ResourceLoader {
	public:
		static std::shared_ptr<Texture2D> LoadTexture(const char* filepath);
		static std::shared_ptr<Shader> LoadShader(const char* filepath);
		static ResourceMetaData GetResourceType(const char* filepath);
	};
}