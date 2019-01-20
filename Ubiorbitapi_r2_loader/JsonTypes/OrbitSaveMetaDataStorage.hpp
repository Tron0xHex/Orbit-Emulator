// OrbitSaveMetaDataStorage.hpp

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     OrbitSaveMetaDataStorage.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

namespace UbiorbitapiR2Loader
{
	using nlohmann::json;

	struct OrbitSaveMetaDataStorage
	{
		std::map<std::string, std::string> saves;
	};
}
