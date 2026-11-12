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

    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    switch (f) {
      case Filter::NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
      case Filter::LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
      default:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    }

    const Def::Uint format = (channels == 4 ? GL_RGBA : GL_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    Img::Image::Clean();
  }
  void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, id);
  }
  void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  void Texture::Clean() {
    Img::Image::Clean();

    if (id != 0) {
      glDeleteTextures(1, &id);
    }

    id = 0;
  }

  Uniform::Uniform(const Def::StringView n, const Def::Uint shader) : name(n){
    id = glGetUniformLocation(shader, name.c_str());
    // TODO: check for errors
  }
  const Def::String &Uniform::Name() const {
    return name;
  }
  Def::Uint Uniform::ID() const {
    return id;
  }

}
