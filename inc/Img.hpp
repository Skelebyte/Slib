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

#include "Def.hpp"
#include "Types.hpp"

namespace Slib::Img {

  struct Image {
    Image() = default;
    Image(const Def::StringView p);
    Image(Def::Uint w, Def::Uint h, const Types::Color255 &a, const Types::Color255 &b);
    ~Image();

    void CheckerImage(Def::Uint w, Def::Uint h, const Types::Color255 &a, const Types::Color255 &b);
    void ErrorImage();

    const Def::Uchar *Data() const;
    Def::Uint Channels() const;
    Def::Uint Width() const;
    Def::Uint Height() const;

  protected:
    void Clean();
    Def::Uchar *data = nullptr;
    Def::Uint channels;
    Def::Uint width;
    Def::Uint height;

  };

}

#endif //SLIB_IMG_HPP
