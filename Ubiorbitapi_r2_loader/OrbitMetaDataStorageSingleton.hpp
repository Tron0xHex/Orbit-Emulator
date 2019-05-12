#pragma once

#include "stdafx.h"
#include "JsonObjects/Generators.hpp"
#include "JsonObjects/OrbitSaveMetaDataStorage.hpp"

using namespace UbiorbitapiR2Loader;

struct OrbitMetaDataStorageHolder
{
	bool Open(const path& filePath);
	bool SetName(int saveId, const string& name);
	string GetName(int saveId);
	bool Remove(int saveId);
	bool Update() const;

private:
	path filePath;
	OrbitSaveMetaDataStorage storage;
};

//------------------------------------------------------------------------------
inline bool OrbitMetaDataStorageHolder::Open(const path& filePath)
{
	this->filePath = filePath;

	if (!exists(filePath))
	{
		auto fs = fstream(filePath, ios::out);

		if (fs)
		{
			fs << R"({"Saves": {}})"_json.dump(4) << endl;
			return true;
		}
	}
	else
	{
		const auto fs = fstream(filePath, ios::in);

		if (fs)
		{
			storage = json::parse(
				static_cast<stringstream const&>(stringstream() << fs.rdbuf()).str());
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------
inline string OrbitMetaDataStorageHolder::GetName(const int saveId)
{
	const auto saveIdString = to_string(saveId);

	if (storage.saves.find(saveIdString) != storage.saves.end())
	{
		return storage.saves.at(saveIdString);
	}

	return "";
}

//------------------------------------------------------------------------------
inline bool OrbitMetaDataStorageHolder::SetName(const int saveId, const string& name)
{
	const auto saveIdString = to_string(saveId);

	if (storage.saves.find(saveIdString) != storage.saves.end())
	{
		storage.saves[saveIdString] = name;
	}
	else
	{
		storage.saves.emplace(saveIdString, name);
	}

	return Update();
}

//------------------------------------------------------------------------------
inline bool OrbitMetaDataStorageHolder::Remove(const int saveId)
{
	const auto saveIdString = to_string(saveId);

	if (storage.saves.find(saveIdString) != storage.saves.end())
	{
		storage.saves.erase(saveIdString);
	}

	return Update();
}

//------------------------------------------------------------------------------
inline bool OrbitMetaDataStorageHolder::Update() const
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

struct OrbitMetaDataStorageSingleton
{
	OrbitMetaDataStorageHolder orbitMetaDataStorageHolder;
	static OrbitMetaDataStorageSingleton& GetInstance();

private:
	OrbitMetaDataStorageSingleton() = default;
	~OrbitMetaDataStorageSingleton() = default;
	OrbitMetaDataStorageSingleton(const OrbitMetaDataStorageSingleton&) = delete;
	OrbitMetaDataStorageSingleton& operator=(const OrbitMetaDataStorageSingleton&) = delete;
};

//------------------------------------------------------------------------------
inline OrbitMetaDataStorageSingleton& OrbitMetaDataStorageSingleton::GetInstance()
{
	static OrbitMetaDataStorageSingleton instance;
	return instance;
}
