//
//  texture.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_opengl_texture_hpp
#define engine_opengl_texture_hpp

#include "opengl.hpp"
#include <glm/vec2.hpp>
#include "../Utils/generic raii.hpp"

namespace GL {
  namespace detail {
    void deleteTexture(const GLuint &);
  }

  template <GLenum TARGET_>
  class Texture {
  public:
    UTILS_RAII_CLASS(Texture, GLuint, id, detail::deleteTexture)
  
    static constexpr GLenum TARGET = TARGET_;
  
    void bind() const {
      glBindTexture(TARGET, id);
      
      CHECK_OPENGL_ERROR();
    }
  
  private:
    GLuint id;
  };
  
  using Texture2D = Texture<GL_TEXTURE_2D>;
  
  template <GLenum TARGET>
  void unbindTexture();
  
  void unbindTexture2D();
  
  struct TexParams2D {
    GLint wrapS = GL_REPEAT;
    GLint wrapT = GL_REPEAT;
    GLint minFilter = GL_NEAREST_MIPMAP_LINEAR;
    GLint magFilter = GL_LINEAR;
    
    void setWrap(GLint);
    void setFilter(GLint);
  };
  
  struct Image2D {
    const void *data = nullptr;
    GLsizei width = 0;
    GLsizei height = 0;
    GLint pitch = 0;
    bool alpha = true;
  };
  
  template <GLenum TARGET>
  Texture<TARGET> makeTexture();
  Texture2D makeTexture2D();
  Texture2D makeTexture2D(const Image2D &, const TexParams2D &);
}

#include "texture.inl"

#endif
