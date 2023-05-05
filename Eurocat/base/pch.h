// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// add headers that you want to pre-compile here
#include "base/framework.h"

#include <string>
#include <format>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <cmath>
#include <functional>
#include <regex>
#include <filesystem>
#include <type_traits>
#include <fstream>
#include <sstream>
#include <mutex>
#include <shared_mutex>
#include <thread>

#include <gdiPlus.h>
#include "spdlog/spdlog.h"

#include "../external/euroscope/include/EuroScopePlugIn.h"

#endif //PCH_H
