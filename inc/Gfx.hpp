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
#include "Types.hpp"
#include <vector>

namespace Slib::Gfx {



  enum struct Filter {
    NEAREST = 0,
    LINEAR = 1,
  };

  struct Texture : Img::Image {
    Texture() = default;
    Texture(Def::StringView p, const Filter &f);
    ~Texture();

    void Setup(const Filter &f);
    void Bind();
    void Unbind();

    protected:
      void Clean();
      Def::Uint id = 0 ;
  };

  struct Uniform {
    Uniform() = default;
    Uniform(Def::StringView n, Def::Uint shader);
    ~Uniform() = default;

    [[nodiscard]] const Def::String &GetName() const;
    [[nodiscard]] Def::Uint GetID() const;

    void Set(Def::Float v);
    void Set(Def::Int v);
    void Set(Def::Bool v);
    void Set(const Types::Color &v);
    void Set(const Types::Vector3f &v);

    protected:
      Def::Int id = -1;
      const Def::String name;
  };

  struct Shader {
    Shader() = default;
    Shader(Def::StringView n, Def::StringView f, Def::StringView v);
    Shader(const Def::Char *f, const Def::Char *v);
    ~Shader();

    void Setup(const Def::Char *f, const Def::Char *v);
    void Clean();

    void Bind();

    [[nodiscard]] bool IsValid() const;

    void AddUniform(Def::StringView n);
    Uniform *GetUniform(Def::StringView n);

    protected:
      Def::Uint id = 0;
      const Def::String name;
      std::vector<Uniform> uniforms;

    private:
      static bool IsCompileOk(Def::Uint s, Def::StringView n);
      static bool IsLinkOk(Def::Uint id);
  };

}

#endif //SLIB_GFX_HPP
