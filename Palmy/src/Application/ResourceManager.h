#pragma once
#include <thread>
#include <atomic>
#include <memory>
#include <unordered_map>
#include "../Rendering/Shader.h"
#include "../Rendering/Texture.h"

namespace Palmy
{
	class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();


	private:
		void CheckFilesForUpdates();
		void LoadShaders();
		void LoadTextures();
	private:
		std::unique_ptr<std::thread> m_FileCheckThread;
		std::atomic<bool> m_FileCheckThreadMustStop;
		std::unordered_map<std::string, std::unique_ptr<Shader>> m_Shaders;
		std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_Textures;

	};
}