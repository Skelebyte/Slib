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

#include "../inc/Types.hpp"
#include "../inc/Util.hpp"
#include <cmath>

namespace Slib::Types {

  Color255::Color255(const Def::Uint8 rgb, const Def::Uint8 alpha) {
    data[0] = rgb;
    data[1] = rgb;
    data[2] = rgb;
    data[3] = alpha;
  }
  Color255::Color255(const Def::Uint8 red, const Def::Uint8 green,
                            const Def::Uint8 blue, const Def::Uint8 alpha) {
    data[0] = red;
    data[1] = green;
    data[2] = blue;
    data[3] = alpha;
  }
  Color255::Color255(const Color &color) {
    data[0] = static_cast<Def::Uint8>(std::round(Util::FloatToColorUint8(color.R()) * 255));
    data[1] = static_cast<Def::Uint8>(std::round(Util::FloatToColorUint8(color.G()) * 255));
    data[2] = static_cast<Def::Uint8>(std::round(Util::FloatToColorUint8(color.B()) * 255));
    data[3] = static_cast<Def::Uint8>(std::round(Util::FloatToColorUint8(color.A()) * 255));
  }
  Def::Uint8 &Color255::R() { return data[0]; }
  Def::Uint8 &Color255::G() { return data[1]; }
  Def::Uint8 &Color255::B() { return data[2]; }
  Def::Uint8 &Color255::A() { return data[3]; }
  const Def::Uint8 &Color255::R() const { return data[0]; }
  const Def::Uint8 &Color255::G() const { return data[1]; }
  const Def::Uint8 &Color255::B() const { return data[2]; }
  const Def::Uint8 &Color255::A() const { return data[3]; }

  Color::Color(const Def::Float rgb, const Def::Float alpha) {
    data[0] = rgb;
    data[1] = rgb;
    data[2] = rgb;
    data[3] = alpha;
  }
  Color::Color(const Def::Float red, const Def::Float green, const Def::Float blue,
                      const Def::Float alpha) {
    data[0] = red;
    data[1] = green;
    data[2] = blue;
    data[3] = alpha;
  }
  Color::Color(const Color255 &color255) {
    data[0] = static_cast<Def::Float>(color255.R()) / 255.0f;
    data[1] = static_cast<Def::Float>(color255.G()) / 255.0f;
    data[2] = static_cast<Def::Float>(color255.B()) / 255.0f;
    data[3] = static_cast<Def::Float>(color255.A()) / 255.0f;
  }
  Def::Float &Color::R() { return data[0]; }
  Def::Float &Color::G() { return data[1]; }
  Def::Float &Color::B() { return data[2]; }
  Def::Float &Color::A() { return data[3]; }
  const Def::Float &Color::R() const { return data[0]; }
  const Def::Float &Color::G() const { return data[1]; }
  const Def::Float &Color::B() const { return data[2]; }
  const Def::Float &Color::A() const { return data[3]; }

  Vector3f::Vector3f(const Def::Float x, const Def::Float y, const Def::Float z) : Vector<Def::Float, 3>() {
    data[0] = x;
    data[1] = y;
    data[2] = z;
  }
  Def::Float &Vector3f::X() { return data[0]; }
  Def::Float &Vector3f::Y() { return data[1]; }
  Def::Float &Vector3f::Z() { return data[2]; }
  const Def::Float &Vector3f::X() const { return data[0]; }
  const Def::Float &Vector3f::Y() const { return data[1]; }
  const Def::Float &Vector3f::Z() const { return data[2]; }
}
