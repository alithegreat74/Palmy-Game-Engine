#pragma once
#include "../Utility/ThreadSafeQueue.h"
#include <unordered_map>
#include "../Rendering/Texture.h"
#include "../Rendering/Shader.h"
#include "AssetMetaGenerator.h"
#include "../WindowsSpecific/WindowsAssetMetaGenerator.h"

namespace Palmy
{
	class ResourceManager {
	public:
		ResourceManager() = default;
		~ResourceManager() = default;
		static std::shared_ptr<Shader>& GetShader(uint32_t);
		static std::shared_ptr<Texture2D>& GetTexture2D(uint32_t);
		static void CheckForResources();
	public:
		inline static ThreadSafeQueue<std::string> s_FileQueue = ThreadSafeQueue<std::string>();
	private:
		inline static std::unordered_map<uint32_t, std::shared_ptr<Shader>> s_Shaders =
			std::unordered_map<uint32_t, std::shared_ptr<Shader>>();
		inline static std::unordered_map<uint32_t, std::shared_ptr<Texture2D>> s_Textures =
			std::unordered_map<uint32_t, std::shared_ptr<Texture2D>>();
#ifdef WINDOWS
		WindowsAssetMetaGenerator m_AssetMetaGenerator;
#else
		AssetMetaGenerator m_AssetMetaGenerator;
#endif
		inline static void* s_MainWindow = nullptr;
	};
}