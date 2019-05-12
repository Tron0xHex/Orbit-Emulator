#pragma once

#include "../stdafx.h"

#include "../OrbitMetaDataStorageSingleton.hpp"

#include "Interfaces/ISavegameWriteListener.hpp"

namespace mg::orbitclient
{
	class UPLAY_API SavegameWriter
	{
		fstream fs{};
		path filePath{};
		unsigned int saveId;
	public:
		SavegameWriter(const path& savePath, unsigned int saveId);
		void Close(bool arg);
		void Write(unsigned int requestId, ISavegameWriteListener* savegameWriteListenerCallBack, void* buff,
		           unsigned int numberOfBytes);
		bool SetName(unsigned short* name);
	};
}

//------------------------------------------------------------------------------
inline mg::orbitclient::SavegameWriter::SavegameWriter(const path& filePath, const unsigned int saveId)
{
	this->saveId = saveId;
	this->filePath = filePath;

	// Create a file in a binary mode.

	fs = fstream(filePath, ios::out | ios::binary | ios::trunc);

	if (!fs)
	{
		LOGD_IF(UPLAY_LOG) << "Unable to open file: " << filePath.string();
	}
}

//------------------------------------------------------------------------------
inline void mg::orbitclient::SavegameWriter::Close(bool arg)
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";

	// Check if all is good and close the stream. 

	if (fs)
	{
		fs.close();
	}
}

//------------------------------------------------------------------------------
inline void mg::orbitclient::SavegameWriter::Write(unsigned int requestUniqueId,
                                                   ISavegameWriteListener* savegameWriteListenerCallBack, void* buff,
                                                   unsigned int numberOfBytes)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId << " SavegameWriteListenerCallBack: " <<
		savegameWriteListenerCallBack
		<< " Buff: " << buff << " NumberOfBytes: " << numberOfBytes;

	// Cast the class to the callback.

	const auto callBack = reinterpret_cast<ISavegameWriteListener::CallBackPtr>(**savegameWriteListenerCallBack->
		callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	// Set file pointer to start.

	fs.seekg(0, ios::beg);

	// Get current pos.

	const auto currentPos = fs.tellp();

	// Write data.

	fs.write(&reinterpret_cast<char*>(buff)[0], numberOfBytes);

	// Check if all is good.

	if (fs)
	{
		// Get the number of bytes written.

		const auto bytesCount = fs.tellp() - currentPos;

		LOGD_IF(UPLAY_LOG) << "Bytes count: " << bytesCount;

		// Execute the callback.

		if (bytesCount > 0 && callBack != nullptr)
		{
			callBack(savegameWriteListenerCallBack, requestUniqueId, bytesCount);
		}
	}
	else
	{
		LOGD_IF(UPLAY_LOG) << "Unable to write file: " << filePath.string();
	}
}

//------------------------------------------------------------------------------
inline bool mg::orbitclient::SavegameWriter::SetName(unsigned short* name)
{
	// Check the ptr for null.

	if (name)
	{
		// Convert the save name to wstring and then to string.

		const auto utf8Name = wstring(reinterpret_cast<wchar_t*>(name));
		const auto utf8NameString = string(utf8Name.begin(), utf8Name.end());

		return OrbitMetaDataStorageSingleton::GetInstance().orbitMetaDataStorageHolder.SetName(saveId, utf8NameString);
	}

	return false;
}
