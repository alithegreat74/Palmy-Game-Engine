#pragma once
#include <thread>
#include <atomic>
#include <mutex>
#include <functional>
#include <filesystem>
#include "../Utility/ThreadSafeQueue.h"
namespace Palmy {
	using AssetMetaGenerationFunction = std::function<void(const std::filesystem::directory_entry&)>;
	class AssetMetaGenerator {
	public:
		AssetMetaGenerator();
		virtual ~AssetMetaGenerator();
	protected:
		void LookUpFiles();
		virtual void LookUpFilesAsync();
		AssetMetaGenerationFunction GetMetaGenerationFunction(const std::filesystem::directory_entry& file)const;
	protected:
		std::thread m_LookUpThread;
		std::atomic<bool> m_LookUpFlag;
		std::unordered_map<std::string, AssetMetaGenerationFunction> m_MetaGenerationFunctions;
	};
	void FolderMeta(const std::filesystem::directory_entry& entry);
	void ShaderMeta(const std::filesystem::directory_entry& entry);
	void TextureMeta(const std::filesystem::directory_entry& entry);
}