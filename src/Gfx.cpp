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

#include "../inc/Gfx.hpp"
#include "../inc/Util.hpp"
#include "../inc/Dbg.hpp"
#include "dep/glad.hpp"

namespace Slib::Gfx {

  Texture::Texture(const Def::StringView p, const Filter &f) : Img::Image(p) {
    Setup(f);
  }
  Texture::~Texture() {
    Clean();
  }
  void Texture::Setup(const Filter &f) {
    if (id == 0) return;
    if (data == nullptr) return;

    glGenTextures(1, &id);
    Dbg::Debug::CheckGL("glGenTextures()");

    glBindTexture(GL_TEXTURE_2D, id);
    Dbg::Debug::CheckGL("glBindTexture()");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    Dbg::Debug::CheckGL("glTexParameteri(GL_TEXTURE_WRAP_S)");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    Dbg::Debug::CheckGL("glTexParameteri(GL_TEXTURE_WRAP_T)");

    switch (f) {
      case Filter::NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        Dbg::Debug::CheckGL("glTexParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST)");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        Dbg::Debug::CheckGL("glTexParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST)");
        break;
      case Filter::LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        Dbg::Debug::CheckGL("glTexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR)");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Dbg::Debug::CheckGL("glTexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR)");
        break;
      default:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        Dbg::Debug::CheckGL("glTexParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST)");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        Dbg::Debug::CheckGL("glTexParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST)");
        break;
    }

    const Def::Uint format = (channels == 4 ? GL_RGBA : GL_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    Dbg::Debug::CheckGL("glTexImage2D()");

    glGenerateMipmap(GL_TEXTURE_2D);
    Dbg::Debug::CheckGL("glGenerateMipmap()");

    Img::Image::Clean();
  }
  void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, id);
    Dbg::Debug::CheckGL("glBindTexture()");
  }
  void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0); // does this need a log??
  }
  void Texture::Clean() {
    Img::Image::Clean();

    if (id != 0) {
      glDeleteTextures(1, &id); // log???
    }

    id = 0;
  }

  Uniform::Uniform(const Def::StringView n, const Def::Uint shader) : name(n){
    id = glGetUniformLocation(shader, name.c_str());
    Dbg::Debug::CheckGL("glGetUniformLocation(" + name + ")");
  }
  const Def::String &Uniform::GetName() const {
    return name;
  }
  Def::Uint Uniform::GetID() const {
    return id;
  }
  void Uniform::Set(const Def::Float v) {
    if (id == -1) return;
    glUniform1f(id, v);
    Dbg::Debug::CheckGL("glUniform1f()");
  }
  void Uniform::Set(const Def::Int v) {
    if (id == -1) return;
    glUniform1i(id, v);
    Dbg::Debug::CheckGL("glUniform1i()");
  }
  void Uniform::Set(const Def::Bool v) {
    if (id == -1) return;
    glUniform1i(id, v);
    Dbg::Debug::CheckGL("glUniform1i(bool)");
  }
  void Uniform::Set(const Types::Color &v) {
    if (id == -1) return;
    glUniform4fv(id, 1, v.data);
    Dbg::Debug::CheckGL("glUniform4fv()");
  }
  void Uniform::Set(const Types::Vector3f &v) {
    if (id == -1) return;
    glUniform3fv(id, 1, v.data);
    Dbg::Debug::CheckGL("glUniform3fv()");
  }


  Shader::Shader(const Def::StringView n, const Def::StringView f, const Def::StringView v) : name(n) {
    if (!Util::File::Exists(f)) return;
    if (!Util::File::Exists(v)) return;

    Def::String fCont = Util::File::Read(f);
    if(fCont.empty()) return;
    const Def::Char *fcstr = fCont.c_str();

    Def::String vCont = Util::File::Read(v);
    if(vCont.empty()) return;
    const Def::Char *vcstr = vCont.c_str();

    Setup(fcstr, vcstr);

  }
  Shader::Shader(const Def::Char *f, const Def::Char *v) {
    Setup(f, v);
  }
  Shader::~Shader() {
    Clean();
  }
    // todo: proper cleanup on early returns
  void Shader::Setup(const Def::Char *f, const Def::Char *v) {
    Def::Uint frag = glCreateShader(GL_FRAGMENT_SHADER);
    Dbg::Debug::CheckGL("glCreateShader(GL_FRAGMENT_SHADER)");

    glShaderSource(frag, 1, &f, nullptr);
    Dbg::Debug::CheckGL("glShaderSource(frag)");

    glCompileShader(frag);
    if(!IsCompileOk(frag, "Fragment")) return;

    Def::Uint vert = glCreateShader(GL_VERTEX_SHADER);
    Dbg::Debug::CheckGL("glCreateShader(GL_VERTEX_SHADER)");

    glShaderSource(vert, 1, &v, nullptr);
    Dbg::Debug::CheckGL("glShaderSource(vert)");

    glCompileShader(vert);
    if(!IsCompileOk(vert, "Vertex")) return;

    id = glCreateProgram();
    Dbg::Debug::CheckGL("glCreateProgram()");

    glAttachShader(id, frag);
    Dbg::Debug::CheckGL("glAttachShader(frag)");

    glAttachShader(id, vert);
    Dbg::Debug::CheckGL("glAttachShader(vert)");

    glLinkProgram(id);
    if(!IsLinkOk(id)) return;

    if(!IsValid()) return;

    glDeleteShader(frag);
    Dbg::Debug::CheckGL("glDeleteShader(frag)");
    glDeleteShader(vert);
    Dbg::Debug::CheckGL("glDeleteShader(vert)");
  }
  void Shader::Clean() {
    if(id != 0) {
      glDeleteProgram(id);
    }

    id = 0;
  }
  void Shader::Bind() {
    if(id == 0) return;

    glUseProgram(id);
    Dbg::Debug::CheckGL("glUseProgram()");
  }
  bool Shader::IsValid() const {
    return glIsProgram(id);
  }
  void Shader::AddUniform(const Def::StringView n) {
    for(Def::Size i = 0; i < uniforms.size(); i++) {
      if (uniforms[i].GetName() == n) return;
    }

    uniforms.emplace_back(n, id);
  }
  Uniform *Shader::GetUniform(const Def::StringView n) {
    for(Def::Size i = 0; i < uniforms.size(); i++) {
      if(uniforms[i].GetName() == n) return &uniforms[i];
    }

    return nullptr;
  }
  bool Shader::IsCompileOk(const Def::Uint s, const Def::StringView n) {
    Def::Int success;
    Def::Char log[512];
    glGetShaderiv(s, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(s, 512, nullptr, log);
      Dbg::Debug::Fatal(Def::String("Compile of ") + n.data() + " is not ok!");
      return true;
    }

    return false;
  }
  bool Shader::IsLinkOk(const Def::Uint id) {
    Def::Int success;
    Def::Char log[512];

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
      glGetProgramInfoLog(id, 512, nullptr, log);
      Dbg::Debug::Fatal(Def::String("Program link is not ok: ") + log);
      return true;
    }

    return false;
  }
}
