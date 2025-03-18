#pragma once
#include "../Rendering/Texture.h"
#include "../Rendering/Shader.h"
#include <memory>
#include <filesystem>

namespace Palmy
{
	class ResourceLoader {
	public:
		static std::shared_ptr<Texture2D> LoadTexture(const char* filePath);
		static std::shared_ptr<Shader> LoadShader(const char* filePath);
	};
}