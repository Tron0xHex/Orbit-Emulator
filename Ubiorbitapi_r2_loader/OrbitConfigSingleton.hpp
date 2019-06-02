#pragma once

#include "stdafx.h"

<<<<<<< HEAD
#include "OrbitConfigHolder.hpp"
=======
#include "JsonObjects/Generators.hpp"
#include "JsonObjects/OrbitConfig.hpp"
>>>>>>> db906bf8a0951915dfc06b52d7c0f80328ae82c8

using namespace UbiorbitapiR2Loader;

struct OrbitConfigHolder
{
<<<<<<< HEAD
=======
	OrbitConfig config;
	void Open(const path&);
};

//------------------------------------------------------------------------------
inline void OrbitConfigHolder::Open(const path& file)
{
	const auto fs = fstream(file, ios::in);
	const auto jsonString = static_cast<stringstream const&>(stringstream() << fs.rdbuf()).str();

	config = json::parse(jsonString);
}

struct OrbitConfigSingleton
{
>>>>>>> db906bf8a0951915dfc06b52d7c0f80328ae82c8
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