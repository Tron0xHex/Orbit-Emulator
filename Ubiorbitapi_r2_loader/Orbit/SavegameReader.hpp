#pragma once

#include "Interfaces/ISavegameReadListener.hpp"

namespace mg::orbitclient {
	struct __declspec(dllexport) SavegameReader {
	private:
		fstream fs_{};
		path filePath_{};
	public:
		SavegameReader(const path& savePath);
		void Close();
		void Read(unsigned int requestUniqueId, ISavegameReadListener *, unsigned int offset, void * buff, unsigned int numberOfBytes);
	};
}

inline mg::orbitclient::SavegameReader::SavegameReader(const path& savePath)
{
	filePath_ = savePath;
	fs_ = fstream(filePath_, ios::in | ios::binary);

	if (!fs_) {
		LOGD_IF(UPLAY_LOG) << "Unable to open file: " << filePath_.string();
	}
}

inline void mg::orbitclient::SavegameReader::Close()
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";

	if (fs_.is_open()) {
		fs_.close();
	}
}

inline void mg::orbitclient::SavegameReader::Read(unsigned int requestUniqueId, ISavegameReadListener * savegameReadListenerCallBack, unsigned int offset, void *buff, unsigned int numberOfBytes)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId << " SavegameReadListenerCallBack: " << savegameReadListenerCallBack
		<< " Buff: " << buff << " NumberOfBytes: " << numberOfBytes << " Offset: " << offset;

	const auto callBack = reinterpret_cast<ISavegameReadListener::CallBackPtr>(**savegameReadListenerCallBack->callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	fs_.seekg(0, ios::beg);
	fs_.read(&static_cast<char*>(buff)[0], numberOfBytes);

	if (fs_) {
		const auto bytesCount = static_cast<unsigned int>(fs_.gcount());

		LOGD_IF(UPLAY_LOG) << "Bytes count: " << bytesCount;

		if (bytesCount > 0 && callBack != nullptr) {
			callBack(savegameReadListenerCallBack, requestUniqueId, bytesCount);
		}
	}
	else {
		LOGD_IF(UPLAY_LOG) << "Unable to read file: " << filePath_.string();
	}
}