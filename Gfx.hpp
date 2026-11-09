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

#ifndef SLIB_GFX_HPP
#define SLIB_GFX_HPP

#include <cstdint>
#if defined(SLIB_GFX_GLAD_INCL)
#include SLIB_GFX_GLAD_INCL
#else
#error ("Must define SLIB_GFX_GLAD_INCL with a valid include path for glad. Example: #define SLIB_GFX_GLAD_INCL \"path/to/glad/glad.h\"")
#endif

#if !defined(SLIB_DBG_HPP)
namespace Slib::Dbg {
struct FuncCall;
}
#endif

namespace Slib::Gfx {

struct Color;

struct Color255 {
  Color255() = default;
  explicit Color255(uint8_t rgb, uint8_t alpha = 255);
  Color255(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
  Color255(const Color &color);
  ~Color255() = default;

  uint8_t &R();
  uint8_t &G();
  uint8_t &B();
  uint8_t &A();

  const uint8_t &R() const;
  const uint8_t &G() const;
  const uint8_t &B() const;
  const uint8_t &A() const;

private:
  uint8_t data[4] = {0, 0, 0, 255};
};
struct Color {
  Color() = default;
  explicit Color(float rgb, float alpha = 1.0f);
  Color(float red, float green, float blue, float alpha = 1.0f);
  Color(const Color255 &color255);
  ~Color() = default;

  float &R();
  float &G();
  float &B();
  float &A();

  const float &R() const;
  const float &G() const;
  const float &B() const;
  const float &A() const;

  float data[4] = {0.0f, 0.0f, 0.0f, 1.0f};
};



}

#if defined(SLIB_GFX_IMPL)
#include <cmath>

namespace Slib::Gfx {

inline Color255::Color255(const uint8_t rgb, const uint8_t alpha) {
  data[0] = rgb;
  data[1] = rgb;
  data[2] = rgb;
  data[3] = alpha;
}
inline Color255::Color255(const uint8_t red, const uint8_t green,
                          const uint8_t blue, const uint8_t alpha) {
  data[0] = red;
  data[1] = green;
  data[2] = blue;
  data[3] = alpha;
}
inline Color255::Color255(const Color &color) {
  data[0] = static_cast<uint8_t>(std::rintf(std::abs(color.R()) * 255));
  data[1] = static_cast<uint8_t>(std::rintf(std::abs(color.G()) * 255));
  data[2] = static_cast<uint8_t>(std::rintf(std::abs(color.B()) * 255));
  data[3] = static_cast<uint8_t>(std::rintf(std::abs(color.A()) * 255));
}
inline uint8_t &Color255::R() { return data[0]; }
inline uint8_t &Color255::G() { return data[1]; }
inline uint8_t &Color255::B() { return data[2]; }
inline uint8_t &Color255::A() { return data[3]; }
inline const uint8_t &Color255::R() const { return data[0]; }
inline const uint8_t &Color255::G() const { return data[1]; }
inline const uint8_t &Color255::B() const { return data[2]; }
inline const uint8_t &Color255::A() const { return data[3]; }

inline Color::Color(const float rgb, const float alpha) {
  data[0] = rgb;
  data[1] = rgb;
  data[2] = rgb;
  data[3] = alpha;
}
inline Color::Color(const float red, const float green, const float blue,
                    const float alpha) {
  data[0] = red;
  data[1] = green;
  data[2] = blue;
  data[3] = alpha;
}
inline Color::Color(const Color255 &color255) {
  data[0] = static_cast<float>(color255.R()) / 255.0f;
  data[1] = static_cast<float>(color255.G()) / 255.0f;
  data[2] = static_cast<float>(color255.B()) / 255.0f;
  data[3] = static_cast<float>(color255.A()) / 255.0f;
}
inline float &Color::R() { return data[0]; }
inline float &Color::G() { return data[1]; }
inline float &Color::B() { return data[2]; }
inline float &Color::A() { return data[3]; }
inline const float &Color::R() const { return data[0]; }
inline const float &Color::G() const { return data[1]; }
inline const float &Color::B() const { return data[2]; }
inline const float &Color::A() const { return data[3]; }

} // namespace Slib::Gfx

#endif

#endif //SLIB_GFX_HPP
