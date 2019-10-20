// OrbitConfig.hpp

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     OrbitConfig.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

#include "Orbit.hpp"

namespace UbiorbitapiR2Loader::JsonObjects
{
	using nlohmann::json;

	struct OrbitConfig
	{
		Orbit orbit;
	};
}
