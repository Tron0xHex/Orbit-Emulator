#pragma once

#include "stdafx.h"

#include "OrbitConfigHolder.hpp"

namespace UbiorbitapiR2Loader
{
	struct OrbitConfigSingleton
	{
		OrbitConfigHolder configHolder;
		static OrbitConfigSingleton& GetInstance();
	private:
		OrbitConfigSingleton() = default;
		~OrbitConfigSingleton() = default;
		OrbitConfigSingleton(const OrbitConfigSingleton&) = delete;
		OrbitConfigSingleton& operator=(const OrbitConfigSingleton&) = delete;
	};

	//------------------------------------------------------------------------------
	inline OrbitConfigSingleton& OrbitConfigSingleton::GetInstance()
	{
		static OrbitConfigSingleton instance;
		return instance;
	}
}
