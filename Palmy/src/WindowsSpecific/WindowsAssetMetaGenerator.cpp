#include "pch.h"
#include "WindowsAssetMetaGenerator.h"
#include "../Core/Core.h"
#include "../Application/ResourceManager.h"
#include "../Utility/StringUtility.h"

namespace Palmy {
	constexpr const char* ASSETS_PATH = "Assets";
	constexpr std::chrono::milliseconds FILE_CHANGE_DEBOUNCE_MILLISECOND(500);
	constexpr size_t BUFFER_SIZE = 1024;
	void WindowsAssetMetaGenerator::LookUpFilesAsync()
	{
		m_DirectoryHandle = CreateFileA(
			ASSETS_PATH,
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			NULL
		);
		ENGINE_ASSERT((m_DirectoryHandle != INVALID_HANDLE_VALUE), "Couldn't create a handle for directory: {0}", ASSETS_PATH);
		char buffer[BUFFER_SIZE];
		DWORD bytesReturned;
		using namespace std::filesystem;
		while (m_LookUpFlag)
		{
			if (!ReadDirectoryChangesW(
				m_DirectoryHandle,
				&buffer,
				sizeof(buffer),
				TRUE,
				FILE_NOTIFY_CHANGE_FILE_NAME |
				FILE_NOTIFY_CHANGE_DIR_NAME |
				FILE_NOTIFY_CHANGE_LAST_WRITE,
				&bytesReturned,
				NULL,
				NULL))
			{
				ENGINE_ERROR("Error while reading file changes");
				continue;
			}
			FILE_NOTIFY_INFORMATION* notification = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(buffer);
			do {
				std::wstring filename(notification->FileName, notification->FileNameLength / sizeof(WCHAR));
				std::string filenameNarrow = StringUtility::ConvertWideString(std::move(filename));
				std::string filepath(ASSETS_PATH);
				filepath += "\\"+filenameNarrow;
				if (!IsDuplicateNotification(filepath))
				{
					directory_entry file(filepath);
					if (file.path().extension()==".meta")
					{
						ResourceManager::s_FileQueue.TryPush(StringUtility::Remove(filepath, ".meta"));
					}
					else if (!exists(filepath+".meta"))
					{
						auto function = GetMetaGenerationFunction(file);
						function(file);
					}
					ResourceManager::s_FileQueue.TryPush(file.path().string());
				}
				if (!notification->NextEntryOffset)
					break;
				notification = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(
					reinterpret_cast<BYTE*>(notification) + notification->NextEntryOffset);
			} while (true);
		}
	}
	bool WindowsAssetMetaGenerator::IsDuplicateNotification(const std::string& filename)
	{
		using namespace std::chrono;
		auto it = m_ChangesTimeStamp.find(filename);
		high_resolution_clock::time_point now = high_resolution_clock::now();
		if (it != m_ChangesTimeStamp.end()) {
			milliseconds duration = duration_cast<milliseconds>(now - it->second);
			if (duration < FILE_CHANGE_DEBOUNCE_MILLISECOND)
				return true;
			it->second = now;
			return false;
		}
		m_ChangesTimeStamp.insert({ filename, now });
		return false;
	}
}
