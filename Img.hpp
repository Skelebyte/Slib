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

#ifndef SLIB_IMG_HPP
#define SLIB_IMG_HPP

#if defined(SLIB_IMG_STBI_INCL)
  #if defined(SLIB_IMG_IMPL)
    #define STB_IMAGE_IMPLEMENTATION
  #endif

  #include SLIB_IMG_STBI_INCL
#elif
  #error ("Must define SLIB_IMG_STBI_INCL with a valid include path for glad. Example: #define SLIB_IMG_STBI_INCL \"path/to/stbi/stb_image.h\"")
#endif

#include "Def.hpp"

namespace Slib::Img {

struct Image {
  Image() = default;
  Image(const Def::StringView &p);
  Image(Def::Uint w, Def::Uint h, const Types::Color255 &a, const Types::Color255 &b);
  ~Image();

  void CheckerImage(Def::Uint w, Def::Uint h, const Types::Color255 &a, const Types::Color255 &b);

protected:
  const Def::Uchar *data = nullptr;
};

}

#if defined(SLIB_IMG_IMPL)

#include "Util.hpp"
#include <cstdlib>

namespace Slib::Img {

inline Image::Image(const Def::StringView &p) {
  if (!Util::File::Exists(p)) return;


}
inline Image::Image(const Def::Uint w, const Def::Uint h, const Types::Color255 &a,
                    const Types::Color255 &b) {
  CheckerImage(w, h, a, b);
}
inline Image::~Image() {
  if (data != nullptr) {
    free(data);

  }
}

} // namespace Slib::Img

#endif

#endif //SLIB_IMG_HPP
