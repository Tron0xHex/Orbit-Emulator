// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN            

#include <windows.h>

#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iterator>
#include <map>
#include <any>
#include <memory>
#include <optional>
#include <mutex>
#include <atomic>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
#include <plog/Log.h>

using namespace std;

using json = nlohmann::json;
using std::filesystem::directory_iterator;
using std::filesystem::path;

static constexpr auto UPLAY_LOG = 0;

// TODO: reference additional headers your program requires here
