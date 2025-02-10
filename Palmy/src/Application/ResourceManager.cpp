#include "pch.h"
#include "ResourceManager.h"

constexpr const char* ASSETS_PATH = "Assets";
constexpr const char* AVAILABLE_TEXTURE_FORMATS[] = { ".png",".jpg"};
constexpr const char* AVAILABLE_SHADER_FORMATS[] = { ".glsl" };

namespace Palmy {
	ResourceManager::ResourceManager()
		:m_FileCheckThreadMustStop(false), m_Shaders(0),m_Textures(0)
	{
		LoadTextures();
		LoadShaders();
		m_FileCheckThread = std::make_unique<std::thread>(&ResourceManager::CheckFilesForUpdates,this);
	}
	ResourceManager::~ResourceManager()
	{
		m_FileCheckThreadMustStop.store(true);
		m_FileCheckThread->join();
	}
	void ResourceManager::CheckFilesForUpdates()
	{
		while (!m_FileCheckThreadMustStop)
		{

		}
	}
	void ResourceManager::LoadTextures()
	{
		using namespace std::filesystem;
		for (const auto& file : recursive_directory_iterator(ASSETS_PATH))
		{
			std::string extension = file.path().extension().string();
			bool isTexture = std::any_of(std::begin(AVAILABLE_TEXTURE_FORMATS), std::end(AVAILABLE_TEXTURE_FORMATS),
				[&extension](const char* format) {return extension == format; });

			if (!isTexture)
				continue;

			std::string filePath = file.path().string();
			auto texture = std::make_unique<Texture2D>(filePath.c_str());
			m_Textures.emplace(filePath, std::move(texture));
		}
	}
	void ResourceManager::LoadShaders()
	{
		using namespace std::filesystem;
		for (const auto& file : recursive_directory_iterator(ASSETS_PATH))
		{
			std::string extension = file.path().extension().string();
			bool isShader = std::any_of(std::begin(AVAILABLE_SHADER_FORMATS), std::end(AVAILABLE_SHADER_FORMATS),
				[&extension](const char* format) {return extension == format; });

			if (!isShader)
				continue;

			std::string filePath = file.path().string();
			auto shader = std::make_unique<Shader>(filePath.c_str());
			m_Shaders.emplace(filePath, std::move(shader));
		}
	}
}
