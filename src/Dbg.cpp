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

#include "../inc/Dbg.hpp"
#include "../inc/Util.hpp"
#include "dep/glad.hpp"
#include <iostream>

namespace Slib::Dbg {

  void Debug::Log(const Def::String &m, const Def::Bool p, const Def::Bool w) {
    Write(m, "LOG", p, w);
  }
  void Debug::Warning(const Def::String &m, const Def::Bool p, const Def::Bool w) {
    Write(m, "WARNING", p, w);
  }
  void Debug::Error(const Def::String &m, const Def::Bool p, const Def::Bool w) {
    Write(m, "ERROR", p, w);
  }
  void Debug::Fatal(const Def::String &m, const Def::Int c, const Def::Bool p, const Def::Bool w) {
    Write(m, "FATAL", p, w);

    Exit(c);
  }
  void Debug::Exit(const Def::Int c, const Def::Bool p, const Def::Bool w) {
    Write("Code: " + Util::ToString(c), "EXIT", p, w);
    std::exit(c);
  }
  void Debug::CheckGL(const Def::String &m, const Def::Bool p, const Def::Bool w) {
    Def::Int err = glGetError();
    if(err != GL_NO_ERROR) {
      Write(m + "OpenGL log: " + Util::ToString(err), "GLAD", p, w);
    }
  }
  void Debug::Write(const Def::String &m, const Def::String &s, Def::Bool p, Def::Bool w, Def::Bool prependTimeAndDate) {
    if (!Util::File::Exists(SLIB_DBG_FILE)) {
      Util::File::Write(SLIB_DBG_FILE, "#### Slib Log File ####");
    }

    Def::String msg;
    if(prependTimeAndDate) {
      msg = Util::Time::TimeAndDateAsString() + " [ " + "DEBUG" + "::" + s.data() + " ] : " + m.data();
    } else {
      msg = Def::String("[ DEBUG::") + s.data() + " ] : " + m.data();
    }

    if(p) {
      std::cout<<msg<<std::endl;
    }

    if(w) {
      Util::File::Write(SLIB_DBG_FILE, msg);
    }
  }

}
