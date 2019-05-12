#pragma once

#include "stdafx.h"

#include "JsonObjects/Generators.hpp"
#include "JsonObjects/OrbitConfig.hpp"

using namespace UbiorbitapiR2Loader;

struct OrbitConfigHolder
{
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