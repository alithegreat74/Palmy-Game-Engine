#include "pch.h"
#include "AssetMetaGenerator.h"
#include <yaml-cpp/yaml.h>
#include "UUID.h"
#include "ResourceManager.h"
#include "../Utility/StringUtility.h"


namespace Palmy {
	constexpr const char* ASSETS_PATH = "Assets";
	constexpr uint16_t LOOKUP_DELAY = 1000;
	AssetMetaGenerator::AssetMetaGenerator()
		:m_LookUpFlag(true), m_MetaGenerationFunctions({ {"",FolderMeta}, {".png",TextureMeta},{".glsl",ShaderMeta},{".jpg",TextureMeta}})
	{
		LookUpFiles();
#ifdef ENGINE_MODE
		m_LookUpThread = std::thread(&AssetMetaGenerator::LookUpFilesAsync, this);
#endif // ENGINE_MODE

	}
	AssetMetaGenerator::~AssetMetaGenerator() {
#ifdef ENGINE_MODE
		m_LookUpFlag.store(false);
		m_LookUpThread.join();
#endif // ENGINE_MODE

	}
	void AssetMetaGenerator::LookUpFiles()
	{
		using namespace std::filesystem;
		for (const auto& file : recursive_directory_iterator(ASSETS_PATH))
		{
			std::string extension = file.path().filename().extension().string();
			if (extension==".meta")
				continue;

			if (!exists(file.path().string() + ".meta"))
			{
				auto function = GetMetaGenerationFunction(file);
				function(file);
			}
			ResourceManager::s_FileQueue.TryPush(file.path().string());
		}
	}
	void AssetMetaGenerator::LookUpFilesAsync()
	{
		using namespace std::filesystem;
		using namespace std::chrono;
		while (m_LookUpFlag)
		{
			//TODO: Instead of checking for changes every 500 milliseconds it's better to find out when the file is modified and handle changes
			auto nowTime = file_clock::now();
			for (const auto& file : recursive_directory_iterator(ASSETS_PATH))
			{
				std::string extension = file.path().filename().extension().string();
				auto lastWriteTime = last_write_time(file);
				if (nowTime - lastWriteTime > std::chrono::milliseconds(LOOKUP_DELAY))
					continue;
				if (extension == ".meta")
				{
					std::string filepath = file.path().string();
					ResourceManager::s_FileQueue.TryPush(StringUtility::Remove(filepath, ".meta"));
					continue;
				}
				if (!exists(file.path().string() + ".meta"))
				{
					auto function = GetMetaGenerationFunction(file);
					function(file);
				}
				ResourceManager::s_FileQueue.TryPush(file.path().string());
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(LOOKUP_DELAY));
		}
	}

	AssetMetaGenerationFunction AssetMetaGenerator::GetMetaGenerationFunction(const std::filesystem::directory_entry& file) const
	{
		auto it = m_MetaGenerationFunctions.find(file.path().filename().extension().string());
		return it->second;
	}
	void FolderMeta(const std::filesystem::directory_entry& entry)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Id" << YAML::Value << UUID::CreateId(entry.path().string());
		out << YAML::Key << "Name" << YAML::Value << entry.path().filename().string().c_str();
		out << YAML::Key << "Type" << YAML::Value << "Folder";
		out << YAML::EndMap;
		std::ofstream fout(entry.path().string() + ".meta");
		fout << out.c_str();
		fout.close();
	}
	void ShaderMeta(const std::filesystem::directory_entry& entry)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Id" << YAML::Value << UUID::CreateId(entry.path().string());
		out << YAML::Key << "Name" << YAML::Value << entry.path().filename().string().c_str();
		out << YAML::Key << "Type" << YAML::Value << "Shader";
		out << YAML::Key << "ShaderType" << YAML::Value << "Vertex";
		out << YAML::EndMap;
		std::ofstream fout(entry.path().string() + ".meta");
		fout << out.c_str();
		fout.close();
	}
	void TextureMeta(const std::filesystem::directory_entry& entry)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Id" << YAML::Value << UUID::CreateId(entry.path().string());
		out << YAML::Key << "Name" << YAML::Value << entry.path().filename().string().c_str();
		out << YAML::Key << "Type" << YAML::Value << "Texture";
		out << YAML::EndMap;
		std::ofstream fout(entry.path().string() + ".meta");
		fout << out.c_str();
		fout.close();
	}
}