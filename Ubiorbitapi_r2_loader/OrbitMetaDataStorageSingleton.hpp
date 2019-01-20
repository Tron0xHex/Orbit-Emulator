#pragma once

#include "stdafx.h"
#include "JsonTypes/Generators.hpp"
#include "JsonTypes/OrbitSaveMetaDataStorage.hpp"

using namespace UbiorbitapiR2Loader;

struct OrbitMetaDataStorageSingleton
{
	static OrbitMetaDataStorageSingleton& GetInstance();

	bool Open(const path& _filePath);
	string GetName(int saveId);
	bool SetName(int saveId, const string& name);
	bool Remove(int saveId);
private:
	OrbitSaveMetaDataStorage m_storage;
	path m_filePath;

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
	m_filePath = _filePath;

	if (!exists(m_filePath)) {
		auto fs = fstream(m_filePath, ios::out);

		if (fs.is_open())
		{
			fs << R"({"Saves": {}})"_json.dump(4) << endl;
			return true;
		}
	}
	else {
		const auto fs = fstream(m_filePath, ios::in);

		if (fs.is_open())
		{
			m_storage = json::parse(
				static_cast<stringstream const&>(stringstream() << fs.rdbuf()).str());
			return true;
		}
	}

	return false;
}

inline string OrbitMetaDataStorageSingleton::GetName(int saveId)
{
	const auto saveIdString = to_string(saveId);

	if (m_storage.saves.find(saveIdString) != m_storage.saves.end()) {
		return m_storage.saves.at(saveIdString);
	}

	return "";
}

inline bool OrbitMetaDataStorageSingleton::SetName(int saveId, const string & name)
{
	const auto saveIdString = to_string(saveId);

	if (m_storage.saves.find(saveIdString) != m_storage.saves.end()) {
		m_storage.saves[saveIdString] = name;
	}
	else {
		m_storage.saves.emplace(saveIdString, name);
	}

	return Update();
}

inline bool OrbitMetaDataStorageSingleton::Remove(int saveId)
{
	const auto saveIdString = to_string(saveId);

	if (m_storage.saves.find(saveIdString) != m_storage.saves.end()) {
		m_storage.saves.erase(saveIdString);
	}

	return Update();
}

inline bool OrbitMetaDataStorageSingleton::Update() const
{
	json json;
	to_json(json, m_storage);

	auto fs = fstream(m_filePath, ios::out | ios::trunc);

	if (fs)
	{
		fs << json.dump(4) << endl;
		return true;
	}

	return false;
}

