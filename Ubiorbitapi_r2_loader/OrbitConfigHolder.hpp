#pragma once

#include "JsonObjects/Generators.hpp"
#include "JsonObjects/OrbitConfig.hpp"

struct OrbitConfigHolder
{
	UbiorbitapiR2Loader::OrbitConfig config;
	void Open(const path&);
};

//------------------------------------------------------------------------------
inline void OrbitConfigHolder::Open(const path& file)
{
	const auto fs = fstream(file, ios::in);
	const auto jsonString = static_cast<stringstream const&>(stringstream() << fs.rdbuf()).str();

	config = json::parse(jsonString);
}