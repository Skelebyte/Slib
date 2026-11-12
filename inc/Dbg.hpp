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

#ifndef SLIB_DBG_HPP
#define SLIB_DBG_HPP

#include "Def.hpp"

#if !defined(SLIB_DBG_FILE)
#define SLIB_DBG_FILE ".slib.log"
#endif

namespace Slib::Dbg {



  struct Debug {
    static void Log(const Def::String &m, Def::Bool p = true, Def::Bool w = true);
    static void Warning(const Def::String &m, Def::Bool p = true, Def::Bool w = true);
    static void Error(const Def::String &m, Def::Bool p = true, Def::Bool w = true);
    static void Fatal(const Def::String &m, Def::Int c = -1, Def::Bool p = true, Def::Bool w = true);
    static void Exit(Def::Int c = -1, Def::Bool p = true, Def::Bool w = true);
    static void CheckGL(const Def::String &m = "", Def::Bool p = true, Def::Bool w = true);

    protected:
      static void Write(const Def::String &m, const Def::String &s, Def::Bool p, Def::Bool w, Def::Bool prependTimeAndDate = true);

  };

}

#endif //SLIB_DBG_HPP
