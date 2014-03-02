/**
 * \file GeometryCore.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include "GeometryCore.h"
#include "RenderState.h"
#include "scg_utilities.h"

namespace scg {


GeometryCore::GeometryCore(GLenum primitiveType, DrawMode drawMode)
    : primitiveType_(primitiveType), drawMode_(drawMode), vao_(0),
      vboIndex_(0), nElements_(0) {
  switch(drawMode_) {
  case DrawMode::ARRAYS:
    drawFunc_ = std::bind(&glDrawArrays, std::placeholders::_1, 0, std::placeholders::_2);
    break;
  case DrawMode::ELEMENTS:
    drawFunc_ = std::bind(&glDrawElements, std::placeholders::_1, std::placeholders::_2,
        GL_UNSIGNED_INT, static_cast<const GLvoid*>(nullptr));
    break;
  default:
    assert(!"Unknown drawMode [GeometryCore::GeometryCore()]");
    break;
  }
  glGenVertexArrays(1, &vao_);

  assert(!checkGLError());
}


GeometryCore::~GeometryCore() {
  if (isGLContextActive()) {
#ifdef SCG_CPP11_RANGE_BASED_FOR
    for (auto vbo : vboAttributes_) {
#else
    // iterator fallback
    for (auto it = vboAttributes_.begin(); it < vboAttributes_.end(); ++it) {
      auto vbo = *it;
#endif
      glDeleteBuffers(1, &vbo);
    }
    glDeleteBuffers(1, &vboIndex_);
    glDeleteVertexArrays(1, &vao_);
  }
}


GeometryCoreSP GeometryCore::create(GLenum primitiveType, DrawMode drawMode) {
  return std::make_shared<GeometryCore>(primitiveType, drawMode);
}


GeometryCore* GeometryCore::addAttributeData(GLuint location, const GLfloat* data, GLsizeiptr size, GLint dim, GLenum usage) {
  glBindVertexArray(vao_);
  assert(glIsVertexArray(vao_));
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  assert(glIsBuffer(vbo));
  vboAttributes_.push_back(vbo);
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
  if (drawMode_ == DrawMode::ARRAYS && nElements_ == 0) {
    nElements_ = size / (dim * sizeof(GLfloat));
  }
  glVertexAttribPointer(location, dim, GL_FLOAT, GL_FALSE, 0, static_cast<const GLvoid*>(0));
  glEnableVertexAttribArray(location);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  assert(!checkGLError());
  return this;
}


GeometryCore* GeometryCore::setElementIndexData(const GLuint* data, GLsizeiptr size, GLenum usage) {
  glBindVertexArray(vao_);
  assert(glIsVertexArray(vao_));
  glGenBuffers(1, &vboIndex_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex_);
  assert(glIsBuffer(vboIndex_));
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
  if (drawMode_ == DrawMode::ELEMENTS) {
    nElements_ = size / sizeof(GLuint);
  }
  // Note: GL_ELEMENT_ARRAY_BUFFER has to be kept bound
  glBindVertexArray(0);

  assert(!checkGLError());
  return this;
}


int GeometryCore::getNTriangles() const {
  int result;
  switch (primitiveType_) {
  case GL_TRIANGLES:
    result = nElements_ / 3;
    break;
  case GL_TRIANGLE_FAN:
  case GL_TRIANGLE_STRIP:
    result = nElements_ - 2;
    break;
  default:
    result = 0;
    break;
  }
  return result;
}


void GeometryCore::render(RenderState* renderState) {
  // pass matrices and other state variables to shader
  renderState->passToShader();

  // draw primitives
  glBindVertexArray(vao_);
  assert(glIsVertexArray(vao_));
  assert(drawFunc_ != nullptr);
  drawFunc_(primitiveType_, nElements_);
  glBindVertexArray(0);

  assert(!checkGLError());
}


} /* namespace scg */
