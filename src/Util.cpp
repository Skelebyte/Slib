/*
 * zlib License
 *
 * (C) 2026 Skelebyte
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * . This notice may not be removed or altered from any source distribution.
 */

#include "../inc/Util.hpp"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <format>

namespace Slib::Util {

  Def::Uint8 FloatToColorUint8(const Def::Float a) {
    if (a > 1.0f) return 1;
    if (a < 0.0f) return 0;

    return static_cast<Def::Uint8>(a);
  }

  Def::String File::Read(const Def::StringView p) {
    if (!Exists(p)) return {};

    std::fstream file(p.data(), std::ios::in);
    if (!file.is_open()) return {};

    Def::String s;

    for (Def::String line; std::getline(file, line);) {
      s.append(line + '\n');
    }

    file.close();

    return s;
  }
  void File::Write(const Def::StringView p, const Def::StringView c, const Def::Int b) {
    std::fstream file(p.data(), (b < 0 ? std::ios::app : std::ios::out));
    if (!file.is_open()) return;

    file << c.data();
    if (b == File::APPEND_NL) file<<std::endl;

    file.close();
  }
  Def::Bool File::Exists(const Def::StringView p) { return std::filesystem::exists(p); }
  Def::String File::GetExtension(const Def::StringView p) {
    if (!Exists(p)) return {};

    return static_cast<std::filesystem::path>(p).extension().string();
  }

  Def::String Time::TimeAsString() {
    const std::chrono::time_point now = std::chrono::system_clock::now();
    const std::chrono::time_point fixed = std::chrono::floor<std::chrono::duration<long long, std::centi>>(now);

    return std::format("{:%H:%M:%S}", fixed);
  }
  Def::String Time::DateAsString() {
    const std::chrono::time_point now = std::chrono::system_clock::now();

    return std::format("{:%d/%m/%Y}", now);
  }
  Def::String Time::TimeAndDateAsString() {
    return TimeAsString() + ", " + DateAsString();
  }

}
