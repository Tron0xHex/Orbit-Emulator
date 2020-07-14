#pragma once

#include "../stdafx.h"
#include "../OrbitMetaDataStorageSingleton.hpp"
#include "Interfaces/ISavegameWriteListener.hpp"

// ReSharper disable CppInconsistentNaming
namespace mg::orbitclient
// ReSharper restore CppInconsistentNaming
{
	class UPLAY_API SavegameWriter
	{
		fstream fs{};
		path filePath{};
		unsigned int saveId;
	public:
		SavegameWriter(const path& filePath, unsigned int saveId);
		void Close(bool arg);
		void Write(unsigned int requestUniqueId, ISavegameWriteListener* savegameWriteListenerCallBack, void* buff,
		           unsigned int numberOfBytes);
		bool SetName(unsigned short* name);
	};
}

//------------------------------------------------------------------------------
inline mg::orbitclient::SavegameWriter::SavegameWriter(const path& filePath, const unsigned int saveId)
{
	this->saveId = saveId;
	this->filePath = filePath;

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

	const auto callBack = reinterpret_cast<ISavegameWriteListener::CallBackPtr>(**savegameWriteListenerCallBack->
		callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;


	fs.seekg(0, ios::beg);

	const auto currentPosition = fs.tellp();

	fs.write(&reinterpret_cast<char*>(buff)[0], numberOfBytes);

	if (fs)
	{
		const auto bytesCount = fs.tellp() - currentPosition;

		LOGD_IF(UPLAY_LOG) << "Bytes count: " << bytesCount;

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
// ReSharper disable CppMemberFunctionMayBeConst
inline bool mg::orbitclient::SavegameWriter::SetName(unsigned short* name)
// ReSharper restore CppMemberFunctionMayBeConst
{
	if (name)
	{
		const auto utf8Name = wstring(reinterpret_cast<wchar_t*>(name));
		const auto utf8NameString = string(utf8Name.begin(), utf8Name.end());

		return UbiorbitapiR2Loader::OrbitMetaDataStorageSingleton::GetInstance().orbitMetaDataStorageHolder.SetName(saveId, utf8NameString);
	}

	return false;
}
