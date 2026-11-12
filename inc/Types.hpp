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
#include "Util.hpp"
#include <cassert>
#include <cmath>

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

    Def::Uint8 data[4] = {0, 0, 0, 255};
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

  template <typename T, Def::Uint S>
  struct Vector : Util::IToString {
    Vector() = default;
    Vector(const T v) {
      for (Def::Uint i = 0; i < S; i++) {
        data[i] = v;
      }
    }
    ~Vector() = default;

    [[nodiscard]] inline Def::Float Length() const {
      Def::Float result = 0.0f;

      for (Def::Uint i = 0; i < S; i++) {
        result += data[i] * data[i];
      }

      return std::sqrt(result);
    }

    [[nodiscard]] inline Vector<T, S> Normalized() const {
      Vector<T, S> result(0.0f);

      const Def::Float len = Length();

      for (Def::Uint i = 0; i < S; i++) {
        result.data[i] += static_cast<Def::Float>(data[i]) / len;
      }

      assert(result.Length());
      // assert(result.Length() == 1.0f);

      return result;
    }

    inline Def::String ToString() const override {
      Def::String result("(");

      for (Def::Uint i = 0; i < S; i++) {
        if (i == S - 1) {
          result.append(Util::ToString(data[i]));
        } else {
          result.append(Util::ToString(data[i]) + ", ");
        }
      }

      result.append(")");

      return result;
    }

    T data[S] = {};
  };

  struct Vector3f : Vector<Def::Float, 3> {
    Vector3f() = default;
    Vector3f(Def::Float x, Def::Float y, Def::Float z);
    ~Vector3f() = default;

    Def::Float &X();
    Def::Float &Y();
    Def::Float &Z();

    [[nodiscard]] const Def::Float &X() const ;
    [[nodiscard]] const Def::Float &Y() const ;
    [[nodiscard]] const Def::Float &Z() const ;
  };

}

#endif //SLIB_TYPES_HPP
