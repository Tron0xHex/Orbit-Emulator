#pragma once

#include "stdafx.h"
#include "JsonTypes/Generators.hpp"
#include "JsonTypes/OrbitSaveMetaDataStorage.hpp"

using namespace UbiorbitapiR2Loader;

struct OrbitMetaDataStorageSingleton
{
	static OrbitMetaDataStorageSingleton& GetInstance();

	bool Open(const path& filePath);
	string GetName(int saveId);
	bool SetName(int saveId, const string& name);
	bool Remove(int saveId);
private:
	OrbitSaveMetaDataStorage storage_;
	path filePath_;

	OrbitMetaDataStorageSingleton() = default;
	~OrbitMetaDataStorageSingleton() = default;
	OrbitMetaDataStorageSingleton(const OrbitMetaDataStorageSingleton&) = delete;
	OrbitMetaDataStorageSingleton& operator=(const OrbitMetaDataStorageSingleton&) = delete;

	bool Update() const;
};

inline OrbitMetaDataStorageSingleton& OrbitMetaDataStorageSingleton::GetInstance()
{
	static OrbitMetaDataStorageSingleton instance;
	return instance;
}

inline bool OrbitMetaDataStorageSingleton::Open(const path& _filePath)
{
	filePath_ = _filePath;

	if (!exists(filePath_)) {
		auto fs = fstream(filePath_, ios::out);

		if (fs.is_open())
		{
			fs << R"({"Saves": {}})"_json.dump(4) << endl;
			return true;
		}
	}
	else {
		const auto fs = fstream(filePath_, ios::in);

		if (fs.is_open())
		{
			storage_ = json::parse(
				static_cast<stringstream const&>(stringstream() << fs.rdbuf()).str());
			return true;
		}
	}

	return false;
}

inline string OrbitMetaDataStorageSingleton::GetName(const int saveId)
{
	const auto saveIdString = to_string(saveId);

	if (storage_.saves.find(saveIdString) != storage_.saves.end()) {
		return storage_.saves.at(saveIdString);
	}

	return "";
}

inline bool OrbitMetaDataStorageSingleton::SetName(const int saveId, const string & name)
{
	const auto saveIdString = to_string(saveId);

	if (storage_.saves.find(saveIdString) != storage_.saves.end()) {
		storage_.saves[saveIdString] = name;
	}
	else {
		storage_.saves.emplace(saveIdString, name);
	}

	return Update();
}

inline bool OrbitMetaDataStorageSingleton::Remove(const int saveId)
{
	const auto saveIdString = to_string(saveId);

	if (storage_.saves.find(saveIdString) != storage_.saves.end()) {
		storage_.saves.erase(saveIdString);
	}

	return Update();
}

inline bool OrbitMetaDataStorageSingleton::Update() const
{
	json json;
	to_json(json, storage_);

	auto fs = fstream(filePath_, ios::out | ios::trunc);

	if (fs)
	{
		fs << json.dump(4) << endl;
		return true;
	}

	return false;
}

