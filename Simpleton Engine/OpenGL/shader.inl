//
//  shader.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static char buffer.hpp"

inline void GL::detail::deleteShader(const GLuint id) {
  glDeleteShader(id);
  
  CHECK_OPENGL_ERROR();
}

template <GLenum TYPE>
void GL::Shader<TYPE>::uploadSource(const GLchar *source, const size_t size) const {
  const GLint length = static_cast<GLint>(size);
  glShaderSource(id, 1, &source, &length);
  
  CHECK_OPENGL_ERROR();
}

template <GLenum TYPE>
bool GL::Shader<TYPE>::compile() const {
  glCompileShader(id);
  GLint status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  CHECK_OPENGL_ERROR();
  return status == GL_TRUE;
}

template <GLenum TYPE>
std::ostream &GL::operator<<(std::ostream &stream, const Shader<TYPE> &shader) {
  GLint logLength;
  glGetShaderiv(shader.id, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength) {
    GLchar *const buf = detail::getCharBuf(logLength);
    glGetShaderInfoLog(shader.id, logLength, nullptr, buf);
    stream << std::string_view(buf, logLength);
  }
  return stream;
}

template <GLenum TYPE>
std::istream &GL::operator>>(std::istream &stream, const Shader<TYPE> &shader) {
  stream.seekg(0, std::ios::seekdir::end);
  const size_t size = stream.tellg();
  GLchar *const source = detail::getCharBuf(static_cast<GLint>(size));
  stream.seekg(0, std::ios::seekdir::beg);
  stream.read(source, size);
  shader.uploadSource(source, size);
  return stream;
}

template <GLenum TYPE>
GL::Shader<TYPE> GL::makeShader() {
  Shader<TYPE> shader(glCreateShader(TYPE));
  CHECK_OPENGL_ERROR();
  return shader;
}

template <GLenum TYPE>
GL::Shader<TYPE> GL::makeShader(const GLchar *source, const size_t size) {
  Shader<TYPE> shader = makeShader<TYPE>();
  shader.uploadSource(source, size);
  if (!shader.compile()) {
    std::cerr << "Failed to compile " << ShaderName<TYPE>::value << " shader\n";
  }
  std::cerr << ShaderName<TYPE>::value << " shader info log:\n" << shader << '\n';
  return shader;
}

template <GLenum TYPE>
GL::Shader<TYPE> GL::makeShader(std::istream &stream) {
  Shader<TYPE> shader = makeShader<TYPE>();
  stream >> shader;
  if (!shader.compile()) {
    std::cerr << "Failed to compile " << ShaderName<TYPE>::value << " shader\n";
  }
  std::cerr << ShaderName<TYPE>::value << " shader info log:\n" << shader << '\n';
  return shader;
}

inline GL::VertShader GL::makeVertShader() {
  return makeShader<GL_VERTEX_SHADER>();
}

inline GL::VertShader GL::makeVertShader(const GLchar *source, const size_t size) {
  return makeShader<GL_VERTEX_SHADER>(source, size);
}

inline GL::VertShader GL::makeVertShader(std::istream &stream) {
  return makeShader<GL_VERTEX_SHADER>(stream);
}

inline GL::FragShader GL::makeFragShader() {
  return makeShader<GL_FRAGMENT_SHADER>();
}

inline GL::FragShader GL::makeFragShader(const GLchar *source, const size_t size) {
  return makeShader<GL_FRAGMENT_SHADER>(source, size);
}

inline GL::FragShader GL::makeFragShader(std::istream &stream) {
  return makeShader<GL_FRAGMENT_SHADER>(stream);
}
