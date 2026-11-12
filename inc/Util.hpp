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

namespace Slib::Util {

  template <typename T>
  inline Def::String ToString(const T &t) {
    return std::to_string(t);
  }

  Def::Uint8 FloatToColorUint8(Def::Float a);

  struct IToString {
    virtual Def::String ToString() const = 0;
  };

  struct File {
    enum {
      APPEND = -1,
      APPEND_NL = -2,
      OVERWRITE = 1
    };

    static Def::String Read(const Def::StringView p);
    static void Write(const Def::StringView p, const Def::StringView c, Def::Int b = APPEND_NL);
    static Def::Bool Exists(const Def::StringView p);
    static Def::String GetExtension(const Def::StringView p);
  };

}

#endif //SLIB_UTIL_HPP
