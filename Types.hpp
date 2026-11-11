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

#ifndef SLIB_TYPES_HPP
#define SLIB_TYPES_HPP

#include "Def.hpp"

namespace Slib::Types {

struct Color;

struct Color255 {
  Color255() = default;
  explicit Color255(Def::Uint8 rgb, Def::Uint8 alpha = 255);
  Color255(Def::Uint8 red, Def::Uint8 green, Def::Uint8 blue, Def::Uint8 alpha = 255);
  Color255(const Color &color);
  ~Color255() = default;

  Def::Uint8 &R();
  Def::Uint8 &G();
  Def::Uint8 &B();
  Def::Uint8 &A();

  [[nodiscard]] const Def::Uint8 &R() const;
  [[nodiscard]] const Def::Uint8 &G() const;
  [[nodiscard]] const Def::Uint8 &B() const;
  [[nodiscard]] const Def::Uint8 &A() const;

private:
  uint8_t data[4] = {0, 0, 0, 255};
};
struct Color {
  Color() = default;
  explicit Color(Def::Float rgb, Def::Float alpha = 1.0f);
  Color(Def::Float red, Def::Float green, Def::Float blue, Def::Float alpha = 1.0f);
  Color(const Color255 &color255);
  ~Color() = default;

  Def::Float &R();
  Def::Float &G();
  Def::Float &B();
  Def::Float &A();

  [[nodiscard]] const Def::Float &R() const;
  [[nodiscard]] const Def::Float &G() const;
  [[nodiscard]] const Def::Float &B() const;
  [[nodiscard]] const Def::Float &A() const;

  Def::Float data[4] = {0.0f, 0.0f, 0.0f, 1.0f};
};


}

#if defined(SLIB_TYPES_IMPL)

inline Color255::Color255(const Def::Uint8 rgb, const Def::Uint8 alpha) {
  data[0] = rgb;
  data[1] = rgb;
  data[2] = rgb;
  data[3] = alpha;
}
inline Color255::Color255(const Def::Uint8 red, const Def::Uint8 green,
                          const Def::Uint8 blue, const Def::Uint8 alpha) {
  data[0] = red;
  data[1] = green;
  data[2] = blue;
  data[3] = alpha;
}
inline Color255::Color255(const Color &color) {
  data[0] = static_cast<Def::Uint8>(std::round(FloatToColorUint8(color.R()) * 255));
  data[1] = static_cast<Def::Uint8>(std::round(FloatToColorUint8(color.G()) * 255));
  data[2] = static_cast<Def::Uint8>(std::round(FloatToColorUint8(color.B()) * 255));
  data[3] = static_cast<Def::Uint8>(std::round(FloatToColorUint8(color.A()) * 255));
}
inline Def::Uint8 &Color255::R() { return data[0]; }
inline Def::Uint8 &Color255::G() { return data[1]; }
inline Def::Uint8 &Color255::B() { return data[2]; }
inline Def::Uint8 &Color255::A() { return data[3]; }
inline const Def::Uint8 &Color255::R() const { return data[0]; }
inline const Def::Uint8 &Color255::G() const { return data[1]; }
inline const Def::Uint8 &Color255::B() const { return data[2]; }
inline const Def::Uint8 &Color255::A() const { return data[3]; }

inline Color::Color(const Def::Float rgb, const Def::Float alpha) {
  data[0] = rgb;
  data[1] = rgb;
  data[2] = rgb;
  data[3] = alpha;
}
inline Color::Color(const Def::Float red, const Def::Float green, const Def::Float blue,
                    const Def::Float alpha) {
  data[0] = red;
  data[1] = green;
  data[2] = blue;
  data[3] = alpha;
}
inline Color::Color(const Color255 &color255) {
  data[0] = static_cast<Def::Float>(color255.R()) / 255.0f;
  data[1] = static_cast<Def::Float>(color255.G()) / 255.0f;
  data[2] = static_cast<Def::Float>(color255.B()) / 255.0f;
  data[3] = static_cast<Def::Float>(color255.A()) / 255.0f;
}
inline Def::Float &Color::R() { return data[0]; }
inline Def::Float &Color::G() { return data[1]; }
inline Def::Float &Color::B() { return data[2]; }
inline Def::Float &Color::A() { return data[3]; }
inline const Def::Float &Color::R() const { return data[0]; }
inline const Def::Float &Color::G() const { return data[1]; }
inline const Def::Float &Color::B() const { return data[2]; }
inline const Def::Float &Color::A() const { return data[3]; }

#endif


#endif //SLIB_TYPES_HPP
