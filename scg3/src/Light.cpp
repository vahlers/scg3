/**
 * \file Light.cpp
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
#include "Light.h"
#include "RenderState.h"
#include "Traverser.h"
#include "scg_utilities.h"

namespace scg {


Light::Light()
  : ubo_(0), position_(0.f, 0.f, 0.f, 1.f), ambient_(0.f, 0.f, 0.f, 1.f),
    diffuse_(0.f, 0.f, 0.f, 1.f), specular_(0.f, 0.f, 0.f, 1.f),
    spotCosCutoff_(0.f), spotExponent_(0.f), modelTransform_(1.0f) {
  glGenBuffers(1, &ubo_);
  assert(!checkGLError());
}


Light::~Light() {
  if (isGLContextActive()) {
    glDeleteBuffers(1, &ubo_);
  }
}


LightSP Light::create() {
  return std::make_shared<Light>();
}


Light* Light::setPosition(const glm::vec4& position) {
  position_ = position;
  return this;
}


Light* Light::setAmbient(const glm::vec4& color) {
  ambient_ = color;
  return this;
}


Light* Light::setDiffuse(const glm::vec4& color) {
  diffuse_ = color;
  return this;
}


Light* Light::setSpecular(const glm::vec4& color) {
  specular_ = color;
  return this;
}


Light* Light::setDiffuseAndSpecular(const glm::vec4& color) {
  diffuse_ = specular_ = color;
  return this;
}


Light* Light::setSpot(const glm::vec3& direction, float cutoffDeg, float exponent) {
  spotDirection_ = glm::vec4(direction, 0.f);
  spotCosCutoff_ = (cutoffDeg > 0.f && cutoffDeg < 90.f) ?
      cos(glm::radians(cutoffDeg)) :  // spotlight
      0.f;                            // no spotlight
  spotExponent_ = exponent;
  return this;
}


void Light::setModelTransform(const glm::mat4 modelTransform) {
  modelTransform_ = modelTransform;
}

void Light::init() {
  GLubyte* buffer = new GLubyte[BUFFER_SIZE];
  // note: position, half vector, and spot direction are updated for each frame in render()
  memcpy(buffer + AMBIENT_OFFSET, glm::value_ptr(ambient_), VEC4_SIZE);
  memcpy(buffer + DIFFUSE_OFFSET, glm::value_ptr(diffuse_), VEC4_SIZE);
  memcpy(buffer + SPECULAR_OFFSET, glm::value_ptr(specular_), VEC4_SIZE);
  memcpy(buffer + SPOT_COS_CUTOFF_OFFSET, &spotCosCutoff_, FLOAT_SIZE);
  memcpy(buffer + SPOT_EXPONENT_OFFSET, &spotExponent_, FLOAT_SIZE);
  glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
  assert(glIsBuffer(ubo_));
  glBufferData(GL_UNIFORM_BUFFER, BUFFER_SIZE, buffer, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  delete [] buffer;
  buffer = nullptr;

  assert(!checkGLError());
}


void Light::accept(Traverser* traverser) {
  traverser->visitLight(this);
}


void Light::acceptPost(Traverser* traverser) {
  traverser->visitPostLight(this);
}


void Light::render(RenderState* renderState) {
  // add light to render state
  renderState->addLight();

  // update light position transformed by model-view transformation
  glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
  assert(glIsBuffer(ubo_));
  glm::mat4 modelViewTransform = renderState->getViewTransform() * modelTransform_;
  glm::vec4 transfPosition = modelViewTransform * position_;
  glBufferSubData(GL_UNIFORM_BUFFER, POSITION_OFFSET, VEC4_SIZE,
      glm::value_ptr(transfPosition));

  // check if half vector or spot direction have to be updated
  if (position_.w < 0.001f) {           // directional light
    // update half vector with fixed view direction (0,0,1) and light direction
    // in eye coordinates, and normalize vector
    glm::vec4 halfVector = glm::normalize(
        glm::vec4(0.f, 0.f, 1.f, 0.f) + glm::normalize(transfPosition));
    glBufferSubData(GL_UNIFORM_BUFFER, HALF_VECTOR_OFFSET, VEC4_SIZE,
        glm::value_ptr(halfVector));
  }
  else if (spotCosCutoff_ >= 0.001f) {  // spotlight
    // update spot direction transformed by model-view transformation,
    // and normalize vector
    glm::vec4 transfSpotDirection = glm::normalize(modelViewTransform * spotDirection_);
    glBufferSubData(GL_UNIFORM_BUFFER, SPOT_DIRECTION_OFFSET, VEC4_SIZE,
        glm::value_ptr(transfSpotDirection));
  }

  // copy buffer contents to light UBO
  glBindBuffer(GL_COPY_WRITE_BUFFER, renderState->getLightUBO());
  glCopyBufferSubData(GL_UNIFORM_BUFFER, GL_COPY_WRITE_BUFFER, 0,
      (renderState->getNLights() - 1) * BUFFER_SIZE, BUFFER_SIZE);
  glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  assert(!checkGLError());
}


void Light::renderPost(RenderState* renderState) {
  // remove light from render state
  renderState->removeLight();
}


} /* namespace scg */
