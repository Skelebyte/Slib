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

#include "Img.hpp"

namespace Slib::Gfx {

  enum struct Filter {
    NEAREST = 0,
    LINEAR = 1,
  };

  struct Texture : Img::Image {
    Texture() = default;
    Texture(const Def::StringView p, const Filter &f);
    ~Texture();

    void Setup(const Filter &f);
    void Bind();
    void Unbind();

    protected:
      void Clean();
      Def::Uint id;
  };

  struct Uniform {
    Uniform(const Def::StringView n, Def::Uint shader);
    ~Uniform() = default;

    const Def::String &Name() const;
    Def::Uint ID() const;

    protected:
      Def::Uint id;
      const Def::String name;
  };

}

#endif //SLIB_GFX_HPP
