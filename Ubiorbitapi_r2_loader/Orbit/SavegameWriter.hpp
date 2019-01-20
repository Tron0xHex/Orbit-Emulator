#pragma once

#include "../stdafx.h"

#include "../OrbitMetaDataStorageSingleton.hpp"

#include "Interfaces/ISavegameWriteListener.hpp"

namespace mg::orbitclient {
	struct __declspec(dllexport) SavegameWriter {
	private:
		fstream fs_{};
		path filePath_{};
		unsigned int saveId_;
	public:
		SavegameWriter(const path& savePath, unsigned int saveId);
		void Close(bool arg);
		void Write(unsigned int requestId, ISavegameWriteListener * savegameWriteListenerCallBack, void * buff, unsigned int numberOfBytes);
		bool SetName(unsigned short * name);
	};
}

inline mg::orbitclient::SavegameWriter::SavegameWriter(const path& savePath, unsigned int saveId)
{
	saveId_ = saveId;
	filePath_ = savePath;
	fs_ = fstream(filePath_, ios::out | ios::binary | ios::trunc);

	if (!fs_) {
		LOGD_IF(UPLAY_LOG) << "Unable to open file: " << filePath_.string();
	}
}

inline void mg::orbitclient::SavegameWriter::Close(bool arg)
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";

	if (fs_.is_open()) {
		fs_.close();
	}
}

inline void mg::orbitclient::SavegameWriter::Write(unsigned int requestUniqueId, ISavegameWriteListener * savegameWriteListenerCallBack, void *buff, unsigned int numberOfBytes)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId << " SavegameWriteListenerCallBack: " << savegameWriteListenerCallBack
		<< " Buff: " << buff << " NumberOfBytes: " << numberOfBytes;

	const auto callBack = reinterpret_cast<ISavegameWriteListener::CallBackPtr>(**savegameWriteListenerCallBack->callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	fs_.seekg(0, ios::beg);

	const auto currentPos = fs_.tellp();

	fs_.write(&reinterpret_cast<char*>(buff)[0], numberOfBytes);

	if (fs_) {
		const auto bytesCount = fs_.tellp() - currentPos;

		LOGD_IF(UPLAY_LOG) << "Bytes count: " << bytesCount;

		if (bytesCount > 0 && callBack != nullptr) {
			callBack(savegameWriteListenerCallBack, requestUniqueId, bytesCount);
		}
	}
	else
	{
		LOGD_IF(UPLAY_LOG) << "Unable to write file: " << filePath_.string();
	}
}

inline bool mg::orbitclient::SavegameWriter::SetName(unsigned short * name)
{
	if (name) {
		const auto utf8Name = wstring(reinterpret_cast<wchar_t*>(name));
		const auto utf8NameString = string(utf8Name.begin(), utf8Name.end());

		return OrbitMetaDataStorageSingleton::GetInstance().SetName(saveId_, utf8NameString);
	}

	return false;
}