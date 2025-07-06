#pragma once
#include "../Application/AssetMetaGenerator.h"
#include <unordered_map>
#include <chrono>
#include <Windows.h>

namespace Palmy {

	class WindowsAssetMetaGenerator :public AssetMetaGenerator {
	public:
		WindowsAssetMetaGenerator()
			:m_ChangesTimeStamp(), m_DirectoryHandle(INVALID_HANDLE_VALUE)
		{
		}
		~WindowsAssetMetaGenerator()override
		{
			CancelIoEx(m_DirectoryHandle, NULL);
			CloseHandle(m_DirectoryHandle);
		}
	protected:
		virtual void LookUpFilesAsync()override;
	private:
		bool IsDuplicateNotification(const std::string&);
	private:
		std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> m_ChangesTimeStamp;
		HANDLE m_DirectoryHandle;
	};
}