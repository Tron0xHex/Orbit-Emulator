#pragma once

#include "stdafx.h"
#include "OrbitMetaDataStorageHolder.hpp"

namespace UbiorbitapiR2Loader
{
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
}
