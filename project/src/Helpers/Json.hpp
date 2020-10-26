#pragma once

#include "src/pch.h"

namespace UbiorbitapiR2Loader
{
	using namespace std;
	using namespace cereal;

	template <class T>
	void SerializeJsonToFile(const path &file, const T &data)
	{
		if (auto fs = fstream(file, ios::out); fs)
		{
			JSONOutputArchive ar(fs);
			ar(data);
			return;
		}

		Fail(fmt::format("File write error: {}", path.string()), true);
	}

	template <class T>
	void DeserializeFromJsonFile(const path &file, T &data)
	{
		if (auto fs = fstream(file, ios::in); fs)
		{
			JSONInputArchive ar(fs);
			ar(data);
			return;
		}

		Fail(fmt::format("File read error: {}", path.string()), true);
	}
} // namespace UbiorbitapiR2Loader
