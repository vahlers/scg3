/**
 * \file MaterialCore.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014-2019 Volker Ahlers
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cassert>
#include <cstring>
#include "MaterialCore.h"
#include "RenderState.h"
#include "scg_utilities.h"

namespace scg {


MaterialCore::MaterialCore()
    : ubo_(0), uboOld_(0),
      emission_(0.0f), ambient_(0.0f), diffuse_(0.0f), specular_(0.0f), shininess_(0.0f) {
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
