#pragma once

#include "Interfaces/ISavegameReadListener.hpp"

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class UPLAY_API SavegameReader
	{
		fstream fs{};
		path filePath{};
	public:
		SavegameReader(const path& savePath);
		void Close();
		void Read(unsigned int requestUniqueId, ISavegameReadListener* savegameReadListenerCallBack,
		          unsigned int offset, void* buff, unsigned int numberOfBytes);
	};
}

//------------------------------------------------------------------------------
inline mg::orbitclient::SavegameReader::SavegameReader(const path& savePath)
{
	filePath = savePath;
	fs = fstream(filePath, ios::in | ios::binary);

	if (!fs)
	{
		LOGD_IF(UPLAY_LOG) << "Unable to open file: " << filePath.string();
	}
}

//------------------------------------------------------------------------------
inline void mg::orbitclient::SavegameReader::Close()
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";

	if (fs.is_open())
	{
		fs.close();
	}
}

//------------------------------------------------------------------------------
inline void mg::orbitclient::SavegameReader::Read(unsigned int requestUniqueId,
                                                  ISavegameReadListener* savegameReadListenerCallBack,
                                                  unsigned int offset, void* buff, unsigned int numberOfBytes)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId << " SavegameReadListenerCallBack: " <<
		savegameReadListenerCallBack
		<< " Buff: " << buff << " NumberOfBytes: " << numberOfBytes << " Offset: " << offset;

	const auto callBack = reinterpret_cast<ISavegameReadListener::CallBackPtr>(**savegameReadListenerCallBack->
		callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	fs.seekg(0, ios::beg);
	fs.read(&static_cast<char*>(buff)[0], numberOfBytes);

	if (fs)
	{
		const auto bytesCount = static_cast<unsigned int>(fs.gcount());

		LOGD_IF(UPLAY_LOG) << "Bytes count: " << bytesCount;

		if (bytesCount > 0 && callBack != nullptr)
		{
			callBack(savegameReadListenerCallBack, requestUniqueId, bytesCount);
		}
	}
	else
	{
		LOGD_IF(UPLAY_LOG) << "Unable to read file: " << filePath.string();
	}
}
