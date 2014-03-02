/**
 * \file MaterialCore.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include <cstring>
#include "MaterialCore.h"
#include "RenderState.h"
#include "scg_utilities.h"

namespace scg {


MaterialCore::MaterialCore()
    : ubo_(0), uboOld_(0) {
  glGenBuffers(1, &ubo_);

  assert(!checkGLError());
}


MaterialCore::~MaterialCore() {
  if (isGLContextActive()) {
    glDeleteBuffers(1, &ubo_);
  }
}


MaterialCoreSP MaterialCore::create() {
  return std::make_shared<MaterialCore>();
}


MaterialCore* MaterialCore::setEmission(const glm::vec4& color) {
  emission_ = color;
  return this;
}


MaterialCore* MaterialCore::setAmbient(const glm::vec4& color) {
  ambient_ = color;
  return this;
}


MaterialCore* MaterialCore::setAmbientAndDiffuse(const glm::vec4& color) {
  ambient_ = diffuse_ = color;
  return this;
}


MaterialCore* MaterialCore::setDiffuse(const glm::vec4& color) {
  diffuse_ = color;
  return this;
}


MaterialCore* MaterialCore::setSpecular(const glm::vec4& color) {
  specular_ = color;
  return this;
}


MaterialCore* MaterialCore::setShininess(GLfloat shininess) {
  shininess_ = shininess;
  return this;
}


void MaterialCore::init() {
  GLubyte* buffer = new GLubyte[BUFFER_SIZE];
  memcpy(buffer + EMISSION_OFFSET, glm::value_ptr(emission_), VEC4_SIZE);
  memcpy(buffer + AMBIENT_OFFSET, glm::value_ptr(ambient_), VEC4_SIZE);
  memcpy(buffer + DIFFUSE_OFFSET, glm::value_ptr(diffuse_), VEC4_SIZE);
  memcpy(buffer + SPECULAR_OFFSET, glm::value_ptr(specular_), VEC4_SIZE);
  memcpy(buffer + SHININESS_OFFSET, &shininess_, FLOAT_SIZE);
  glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
  assert(glIsBuffer(ubo_));
  glBufferData(GL_UNIFORM_BUFFER, BUFFER_SIZE, buffer, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  delete [] buffer;
  buffer = nullptr;

  assert(!checkGLError());
}


void MaterialCore::render(RenderState* renderState) {
  glGetIntegeri_v(GL_UNIFORM_BUFFER_BINDING, OGLConstants::MATERIAL.bindingPoint, &uboOld_);
  glBindBufferBase(GL_UNIFORM_BUFFER, OGLConstants::MATERIAL.bindingPoint, ubo_);
  assert(glIsBuffer(ubo_));

  assert(!checkGLError());
}


void MaterialCore::renderPost(RenderState* renderState) {
  glBindBufferBase(GL_UNIFORM_BUFFER, OGLConstants::MATERIAL.bindingPoint, uboOld_);

  assert(!checkGLError());
}


} /* namespace scg */
