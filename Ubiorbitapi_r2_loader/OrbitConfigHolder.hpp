#pragma once

#include "JsonObjects/Generators.hpp"
#include "JsonObjects/OrbitConfig.hpp"

namespace UbiorbitapiR2Loader
{
	struct OrbitConfigHolder
	{
		UbiorbitapiR2Loader::JsonObjects::OrbitConfig config;
		void Open(const path&);
	};

	//------------------------------------------------------------------------------
	inline void OrbitConfigHolder::Open(const path& file)
	{
		const auto fs = fstream(file, ios::in);
		const auto jsonString = static_cast<stringstream const&>(stringstream() << fs.rdbuf()).str();

		config = json::parse(jsonString);
	}
}
