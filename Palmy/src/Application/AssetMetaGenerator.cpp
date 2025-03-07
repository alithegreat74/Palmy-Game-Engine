#include "pch.h"
#include "AssetMetaGenerator.h"
#include <yaml-cpp/yaml.h>

namespace Palmy {
	constexpr const char* ASSETS_PATH = "Assets";
	AssetMetaGenerator::AssetMetaGenerator()
		:m_LookUpFlag(true), m_MetaGenerationFunctions({ {"",FolderMeta}, {".png",TextureMeta},{".glsl",ShaderMeta},{".jpg",TextureMeta}})
	{
		m_LookUpThread = std::thread(&AssetMetaGenerator::LookUpFiles, this);
	}
	AssetMetaGenerator::~AssetMetaGenerator() {
		m_LookUpFlag.store(false);
		m_LookUpThread.join();
	}

	void AssetMetaGenerator::LookUpFiles()
	{
		using namespace std::filesystem;
		while (m_LookUpFlag)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			for (const auto& file : recursive_directory_iterator(ASSETS_PATH))
			{
				std::string extension = file.path().filename().extension().string();
				if (extension == ".meta" || exists(file.path().string() + ".meta"))
					continue;

				std::lock_guard<std::mutex> lock(m_LookUpMutex);
				auto function = GetMetaGenerationFunction(file);
				function(file);
			}
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
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Name" << YAML::Value << entry.path().filename().string().c_str();
			out << YAML::Key << "Type" << YAML::Value << "Folder";
			out << YAML::EndMap;
		}
		out << YAML::EndMap;
		std::ofstream fout(entry.path().string() + ".meta");
		fout << out.c_str();
	}
	void ShaderMeta(const std::filesystem::directory_entry& entry)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Name" << YAML::Value << entry.path().filename().string().c_str();
			out << YAML::Key << "Type" << YAML::Value << "Shader";
			out << YAML::EndMap;
		}
		out << YAML::EndMap;
		std::ofstream fout(entry.path().string() + ".meta");
		fout << out.c_str();
	}
	void TextureMeta(const std::filesystem::directory_entry& entry)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Name" << YAML::Value << entry.path().filename().string().c_str();
			out << YAML::Key << "Type" << YAML::Value << "Texture";
			out << YAML::EndMap;
		}
		out << YAML::EndMap;
		std::ofstream fout(entry.path().string() + ".meta");
		fout << out.c_str();
	}
}