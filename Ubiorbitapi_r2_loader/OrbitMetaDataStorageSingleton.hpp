#pragma once

#include "stdafx.h"
#include "JsonObjects/Generators.hpp"
#include "JsonObjects/OrbitSaveMetaDataStorage.hpp"

using namespace UbiorbitapiR2Loader;

struct OrbitMetaDataStorageSingleton
{
	static OrbitMetaDataStorageSingleton& GetInstance();

	bool Open(const path& filePath);
	string GetName(int saveId);
	bool SetName(int saveId, const string& name);
	bool Remove(int saveId);
private:
	OrbitSaveMetaDataStorage storage;
	path filePath;

	OrbitMetaDataStorageSingleton() = default;
	~OrbitMetaDataStorageSingleton() = default;
	OrbitMetaDataStorageSingleton(const OrbitMetaDataStorageSingleton&) = delete;
	OrbitMetaDataStorageSingleton& operator=(const OrbitMetaDataStorageSingleton&) = delete;

	bool Update() const;
};

//------------------------------------------------------------------------------
inline OrbitMetaDataStorageSingleton& OrbitMetaDataStorageSingleton::GetInstance()
{
	static OrbitMetaDataStorageSingleton instance;
	return instance;
}

//------------------------------------------------------------------------------
inline bool OrbitMetaDataStorageSingleton::Open(const path& filePath)
{
	this->filePath = filePath;

	if (!exists(filePath)) {
		auto fs = fstream(filePath, ios::out);

		if (fs.is_open())
		{
			fs << R"({"Saves": {}})"_json.dump(4) << endl;
			return true;
		}
	}
	else {
		const auto fs = fstream(filePath, ios::in);

		if (fs.is_open())
		{
			storage = json::parse(
				static_cast<stringstream const&>(stringstream() << fs.rdbuf()).str());
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------
inline string OrbitMetaDataStorageSingleton::GetName(const int saveId)
{
	const auto saveIdString = to_string(saveId);

	if (storage.saves.find(saveIdString) != storage.saves.end()) {
		return storage.saves.at(saveIdString);
	}

	return "";
}

//------------------------------------------------------------------------------
inline bool OrbitMetaDataStorageSingleton::SetName(const int saveId, const string & name)
{
	const auto saveIdString = to_string(saveId);

	if (storage.saves.find(saveIdString) != storage.saves.end()) {
		storage.saves[saveIdString] = name;
	}
	else {
		storage.saves.emplace(saveIdString, name);
	}

	return Update();
}

//------------------------------------------------------------------------------
inline bool OrbitMetaDataStorageSingleton::Remove(const int saveId)
{
	const auto saveIdString = to_string(saveId);

	if (storage.saves.find(saveIdString) != storage.saves.end()) {
		storage.saves.erase(saveIdString);
	}

	return Update();
}

//------------------------------------------------------------------------------
inline bool OrbitMetaDataStorageSingleton::Update() const
{
	json json;
	to_json(json, storage);

	auto fs = fstream(filePath, ios::out | ios::trunc);

	if (fs)
	{
		fs << json.dump(4) << endl;
		return true;
	}

	return false;
}

