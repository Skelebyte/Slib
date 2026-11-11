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

#if defined(SLIB_GFX_GLAD_INCL)
  #include SLIB_GFX_GLAD_INCL
#else
  #error ("Must define SLIB_GFX_GLAD_INCL with a valid include path for glad. Example: #define SLIB_GFX_GLAD_INCL \"path/to/glad/glad.h\"")
#endif

#include "Def.hpp"

namespace Slib::Gfx {

}

#if defined(SLIB_GFX_IMPL)

namespace Slib::Gfx {



} // namespace Slib::Gfx

#endif

#endif //SLIB_GFX_HPP
