// Generators.hpp

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Generators.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

#include "OrbitSaveMetaDataStorage.hpp"
#include "OrbitConfig.hpp"
#include "Orbit.hpp"
#include "Profile.hpp"

namespace nlohmann
{
	void from_json(const json& j, UbiorbitapiR2Loader::OrbitSaveMetaDataStorage& x);
	void to_json(json& j, const UbiorbitapiR2Loader::OrbitSaveMetaDataStorage& x);

	inline void from_json(const json& j, UbiorbitapiR2Loader::OrbitSaveMetaDataStorage& x)
	{
		x.saves = j.at("Saves").get<std::map<std::string, std::string>>();
	}

	inline void to_json(json& j, const UbiorbitapiR2Loader::OrbitSaveMetaDataStorage& x)
	{
		j = json::object();
		j["Saves"] = x.saves;
	}

	void from_json(const json& j, UbiorbitapiR2Loader::Profile& x);
	void to_json(json& j, const UbiorbitapiR2Loader::Profile& x);

	void from_json(const json& j, UbiorbitapiR2Loader::Orbit& x);
	void to_json(json& j, const UbiorbitapiR2Loader::Orbit& x);

	void from_json(const json& j, UbiorbitapiR2Loader::OrbitConfig& x);
	void to_json(json& j, const UbiorbitapiR2Loader::OrbitConfig& x);

	inline void from_json(const json& j, UbiorbitapiR2Loader::Profile& x)
	{
		x.accountId = j.at("AccountId").get<std::string>();
		x.userName = j.at("UserName").get<std::string>();
		x.password = j.at("Password").get<std::string>();
	}

	inline void to_json(json& j, const UbiorbitapiR2Loader::Profile& x)
	{
		j = json::object();
		j["AccountId"] = x.accountId;
		j["UserName"] = x.userName;
		j["Password"] = x.password;
	}

	inline void from_json(const json& j, UbiorbitapiR2Loader::Orbit& x)
	{
		x.profile = j.at("Profile").get<UbiorbitapiR2Loader::Profile>();
		x.saves = j.at("Saves").get<std::string>();
	}

	inline void to_json(json& j, const UbiorbitapiR2Loader::Orbit& x)
	{
		j = json::object();
		j["Profile"] = x.profile;
		j["Saves"] = x.saves;
	}

	inline void from_json(const json& j, UbiorbitapiR2Loader::OrbitConfig& x)
	{
		x.orbit = j.at("Orbit").get<UbiorbitapiR2Loader::Orbit>();
	}

	inline void to_json(json& j, const UbiorbitapiR2Loader::OrbitConfig& x)
	{
		j = json::object();
		j["Orbit"] = x.orbit;
	}
}
