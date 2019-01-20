#pragma once

#include "../stdafx.h"

#include "../Consts.hpp"
#include "../OrbitConfigSingleton.hpp"
#include "../OrbitMetaDataStorageSingleton.hpp"

#include "SavegameInfo.hpp"

#include "Interfaces/IGetSavegameListListener.hpp"
#include "Interfaces/IGetSavegameWriterListener.hpp"
#include "Interfaces/IRemoveSavegameListener.hpp"
#include "Interfaces/IGetSavegameReaderListener.hpp"
#include "Interfaces/IGetLoginDetailsListener.hpp"

static shared_ptr<mg::orbitclient::SavegameReader> saveGameReader{ nullptr };
static shared_ptr<mg::orbitclient::SavegameWriter> saveGameWriter{ nullptr };
static vector<mg::orbitclient::SavegameInfo*> saveInfos{ nullptr };

namespace mg::orbitclient {
	struct __declspec(dllexport) OrbitClient {
	private:
		atomic_int requestUniqueId_ = 0;

		path GetSavePath(unsigned int productId, unsigned int saveId);
		path GetSavesPath(unsigned int productId);
	public:
		OrbitClient();
		void StartProcess(unsigned short *, unsigned short *, unsigned short *);
		bool StartLauncher(unsigned int, unsigned int, char const *, char const *);
		void GetSavegameList(unsigned int requestUniqueId, IGetSavegameListListener * savegameListListenerCallBack, unsigned int productId);
		void GetSavegameWriter(unsigned int requestUniqueId, IGetSavegameWriterListener *, unsigned int productId, unsigned int saveGameId, bool open);
		void GetSavegameReader(unsigned int requestUniqueId, IGetSavegameReaderListener *, unsigned int productId, unsigned int saveGameId);
		void RemoveSavegame(unsigned int requestUniqueId, IRemoveSavegameListener *, unsigned int productId, unsigned int saveGameId);
		void GetLoginDetails(unsigned int requestUniqueId, IGetLoginDetailsListener *);
		unsigned int GetRequestUniqueId();
		unsigned short * GetInstallationErrorString(char const *);
		unsigned int GetInstallationErrorNum();
		void Update();
		~OrbitClient();
	};
}

inline mg::orbitclient::OrbitClient::OrbitClient()
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";
}

inline path mg::orbitclient::OrbitClient::GetSavePath(unsigned int productId, unsigned int saveId)
{
	return path(OrbitConfigSingleton::GetInstance().config.orbit.saves) / path(to_string(productId)) / path(to_string(saveId) + Consts::SaveFileExtension);
}

inline path mg::orbitclient::OrbitClient::GetSavesPath(unsigned int productId)
{
	return path(OrbitConfigSingleton::GetInstance().config.orbit.saves) / path(to_string(productId));
}

inline void mg::orbitclient::OrbitClient::StartProcess(unsigned short *, unsigned short *, unsigned short *)
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";
}

inline void mg::orbitclient::OrbitClient::GetSavegameList(unsigned int requestUniqueId, IGetSavegameListListener * svegameListListenerCallBack, unsigned int productId)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId
		<< " GetSvegameListListenerCallBack: " << svegameListListenerCallBack
		<< " ProductId: " << productId;

	const auto savesPath = GetSavesPath(productId);
	const auto callBack = reinterpret_cast<IGetSavegameListListener::CallBackPtr>(**svegameListListenerCallBack->callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	if (!exists(savesPath)) {
		if (create_directories(savesPath)) {
			callBack(svegameListListenerCallBack, requestUniqueId, nullptr, 0);
			return;
		}
	}
	else {
		for (auto& saveInfo : saveInfos) {
			delete saveInfo;
		}

		saveInfos.clear();

		for (const auto &dirEntry : directory_iterator(savesPath)) {
			const auto file = dirEntry.path();

			if (file.has_extension() && file.extension() == Consts::SaveFileExtension) {
				const auto id = static_cast<unsigned int>(atoi(file.stem().string().c_str()));
				const auto fileSize = static_cast<unsigned long>(file_size(file));
				const auto name = converter.from_bytes(OrbitMetaDataStorageSingleton::GetInstance().GetName(id));
				const auto saveGameInfo = new SavegameInfo(id, productId, fileSize, name);

				LOGD_IF(UPLAY_LOG) << "Save - " << " id: " << id << " size: " << fileSize << " name: " << name << " this ptr: " << saveGameInfo;

				saveInfos.push_back(saveGameInfo);
			}
		}

		if (callBack != nullptr) {
			callBack(svegameListListenerCallBack, requestUniqueId, *saveInfos.data(), saveInfos.size());
		}
	}
}

inline void mg::orbitclient::OrbitClient::GetSavegameReader(unsigned int requestUniqueId, IGetSavegameReaderListener * getSavegameReaderListenerCallBack, unsigned int productId, unsigned int saveId)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId << " GetSavegameReaderListenerCallBack: " << getSavegameReaderListenerCallBack
		<< " ProductId: " << productId << " SaveId: " << saveId;

	const auto callBack = reinterpret_cast<IGetSavegameReaderListener::CallBackPtr>(**getSavegameReaderListenerCallBack->callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	saveGameReader = std::make_shared<SavegameReader>(GetSavePath(productId, saveId));

	if (callBack != nullptr) {
		callBack(getSavegameReaderListenerCallBack, requestUniqueId, NULL, saveGameReader.get());
	}
}

inline void mg::orbitclient::OrbitClient::Update()
{

}

inline bool mg::orbitclient::OrbitClient::StartLauncher(unsigned int, unsigned int, char const *, char const *)
{
	return false;
}

inline unsigned short * mg::orbitclient::OrbitClient::GetInstallationErrorString(char const * err)
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";
	return nullptr;
}

inline unsigned int mg::orbitclient::OrbitClient::GetInstallationErrorNum()
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";
	return 0;
}

inline void mg::orbitclient::OrbitClient::GetSavegameWriter(unsigned int requestUniqueId, IGetSavegameWriterListener * getSavegameWriterListenerCallBack, unsigned int productId, unsigned int saveId, bool open)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId << " GetSavegameWriterListenerCallBack: " << getSavegameWriterListenerCallBack
		<< " ProductId: " << productId << " SaveId: " << saveId;

	const auto callBack = reinterpret_cast<IGetSavegameWriterListener::CallBackPtr>(**getSavegameWriterListenerCallBack->callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	const auto gameSavesPath = GetSavesPath(productId);

	if (!exists(gameSavesPath))
	{
		create_directories(gameSavesPath);
	}

	saveGameWriter = std::make_shared<SavegameWriter>(GetSavePath(productId, saveId), saveId);

	if (callBack != nullptr) {
		callBack(getSavegameWriterListenerCallBack, requestUniqueId, NULL, saveGameWriter.get());
	}
}

inline void mg::orbitclient::OrbitClient::RemoveSavegame(unsigned int requestUniqueId, IRemoveSavegameListener * removeSavegameListenerCallBack, unsigned int productId, unsigned int saveId)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId << " RemoveSavegameListenerCallBack: " << removeSavegameListenerCallBack;

	const auto callBack = reinterpret_cast<IRemoveSavegameListener::CallBackPtr>(**removeSavegameListenerCallBack->callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	const auto savePath = GetSavePath(productId, saveId);

	if (exists(savePath))
	{
		remove(savePath);
	}

	if (callBack != nullptr) {
		callBack(removeSavegameListenerCallBack, requestUniqueId, exists(savePath));
	}
}

inline void mg::orbitclient::OrbitClient::GetLoginDetails(unsigned int requestUniqueId, IGetLoginDetailsListener * getLoginDetailsListenerCallBack)
{
	LOGD_IF(UPLAY_LOG) << "RequestUniqueId: " << requestUniqueId << " GetLoginDetailsListenerCallBack: " << getLoginDetailsListenerCallBack;

	const auto callBack = reinterpret_cast<IGetLoginDetailsListener::CallBackPtr>(**getLoginDetailsListenerCallBack->callBackPtr);

	LOGD_IF(UPLAY_LOG) << "CallBackPtr: " << callBack;

	const auto profile = OrbitConfigSingleton::GetInstance().config.orbit.profile;

	const auto accountId = profile.accountId.c_str();
	const auto userName = profile.userName.c_str();
	const auto password = profile.password.c_str();

	if (callBack != nullptr) {
		callBack(getLoginDetailsListenerCallBack, requestUniqueId, accountId, userName, password);
	}
}

inline unsigned int mg::orbitclient::OrbitClient::GetRequestUniqueId()
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";
	return ++requestUniqueId_;
}

inline mg::orbitclient::OrbitClient::~OrbitClient()
{
	LOGD_IF(UPLAY_LOG) << "__CALL__";

	saveGameReader.reset();
	saveGameWriter.reset();

	for (auto& saveInfo : saveInfos) {
		delete saveInfo;
	}

	saveInfos.clear();
}