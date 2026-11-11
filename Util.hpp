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

#ifndef SLIB_UTIL_HPP
#define SLIB_UTIL_HPP

#include "Def.hpp"
#include <fstream>

namespace Slib::Util {
struct File {
  enum {
    APPEND = -1,
    APPEND_NL = -2,
    OVERWRITE = 1
  };

  static Def::String Read(const Def::StringView &p);
  static void Write(const Def::StringView &p, const Def::StringView &c, Def::Int b = APPEND_NL);
  static Def::Bool Exists(const Def::StringView &p);
  static Def::String GetExtension(const Def::StringView &p);

};

}

#if defined(SLIB_UTIL_IMPL)

#include <filesystem>

namespace Slib::Util {

inline Def::String File::Read(const Def::StringView &p) {
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
inline void File::Write(const Def::StringView &p, const Def::StringView &c, const Def::Int b) {
  std::fstream file(p.data(), (b < 0 ? std::ios::app : std::ios::out));
  if (!file.is_open()) return;

  file << c.data();
  if (b == File::APPEND_NL) file<<std::endl;

  file.close();
}
inline Def::Bool File::Exists(const Def::StringView &p) { return std::filesystem::exists(p); }
inline Def::String File::GetExtension(const Def::StringView &p) {
  if (!Exists(p)) return {};

  return static_cast<std::filesystem::path>(p).extension();
}

} // namespace Slib::Util

#endif

#endif //SLIB_UTIL_HPP
