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

#include "../inc/Img.hpp"
#include "../inc/Util.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "dep/stb_image.h"
#include <cstdlib>

namespace Slib::Img {

  Image::Image(const Def::StringView p) {
    if(!Util::File::Exists(p)) {
      ErrorImage();
      return;
    }

    Def::Int w, h, c;

    data = stbi_load(p.data(), &w, &h, &c, 0);
    if(!data) {
      ErrorImage();
      return;
    }

    width = w;
    height = h;
    channels = c;
  }
  Image::~Image() {
    Clean();
  }
  void Image::CheckerImage(const Def::Uint w, const Def::Uint h, const Types::Color255 &a, const Types::Color255 &b) {
    data = (Def::Uchar *)std::malloc(sizeof(Def::Uchar) * w * h * 4);

    width = w;
    height = h;

    for(Def::Uint x = 0; x < w; x++) {
      for(Def::Uint y = 0; y < h; y++) {
        const Def::Float t = static_cast<Def::Uint>(h) / 2.0f;
        const Def::Float s = static_cast<Def::Uint>(w) / 2.0f;

        Def::Uint i = (x * w  + x) * 4;
        const Def::Uint tw = static_cast<Def::Uint>(t * w);
        const Def::Uint sh = static_cast<Def::Uint>(s * h);
        if(sh + tw % 2 == 0) {
          data[i + 0] = a.R();
          data[i + 1] = a.G();
          data[i + 2] = a.B();
          data[i + 3] = a.A();
        } else {
          data[i + 0] = b.R();
          data[i + 1] = b.G();
          data[i + 2] = b.B();
          data[i + 3] = b.A();
        }
      }
    }
  }
  void Image::ErrorImage() {
    CheckerImage(4, 4, Types::Color255(255, 0, 255), Types::Color255(0));
  }
  const Def::Uchar *Image::Data() const {
    return data;
  }
  Def::Uint Image::Channels() const {
    return channels;
  }
  Def::Uint Image::Width() const {
    return width;
  }
  Def::Uint Image::Height() const {
    return height;
  }
  void Image::Clean() {
    if(data != nullptr) {
      std::free(data);
    }

    data = nullptr;
  }

}
