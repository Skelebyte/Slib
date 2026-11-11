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

#ifndef SLIB_DEF_HPP
#define SLIB_DEF_HPP

#include <cstdint>
#include <string_view>

namespace Slib::Def {
using Uint8 = std::uint8_t;
using Uint16 = std::uint16_t;
using Uint32 = std::uint32_t;
using Uint64 = std::uint64_t;
using Uint = Uint32;

using Int8 = std::int8_t;
using Int16 = std::int16_t;
using Int32 = std::int32_t;
using Int64 = std::int64_t;
using Int = Int32;

using Size = size_t;

using Float = float;
using Double = double;

using Bool = bool;

using Char = char;
using Uchar = unsigned char;

using String = std::string;
using StringView = std::string_view;

Uint8 FloatToColorUint8(Float a);

}

#if defined(SLIB_DEF_IMPL)

namespace Slib::Def {

inline Uint8 FloatToColorUint8(const Float a) {
  if (a > 1.0f) return static_cast<Uint8>(1.0f);
  if (a < 0.0f) return static_cast<Uint8>(0.0f);
  return static_cast<Uint8>(a);
}

}

#endif

#endif //SLIB_DEF_HPP
