#pragma once
#include <thread>
#include <atomic>
#include <mutex>
#include <functional>
#include <filesystem>

namespace Palmy {
	using AssetMetaGenerationFunction = std::function<void(const std::filesystem::directory_entry&)>;
	class AssetMetaGenerator {
	public:
		AssetMetaGenerator();
		~AssetMetaGenerator();
	private:
		void LookUpFiles();
		AssetMetaGenerationFunction GetMetaGenerationFunction(const std::filesystem::directory_entry& file)const;
	private:
		std::thread m_LookUpThread;
		std::atomic<bool> m_LookUpFlag;
		std::mutex m_LookUpMutex;
		std::unordered_map<std::string, AssetMetaGenerationFunction> m_MetaGenerationFunctions;
	};
	void FolderMeta(const std::filesystem::directory_entry& entry);
	void ShaderMeta(const std::filesystem::directory_entry& entry);
	void TextureMeta(const std::filesystem::directory_entry& entry);
}