/**
 * \file StereoCamera.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014 Volker Ahlers
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

#include "../src/RenderState.h"
#include "StereoCamera.h"

namespace scg {

StereoCamera::StereoCamera()
    : Camera(), eyeFactor_(-1) {
  initBourke(60.f, 0.01f, 1000.f, 1.5f, 0.02f);
}

StereoCamera::~StereoCamera() {
}


StereoCameraSP StereoCamera::create() {
  return std::make_shared<StereoCamera>();
}


void StereoCamera::init(GLfloat near, GLfloat far,
    GLfloat screenDist, GLfloat screenHeight, GLfloat interOcularDist) {
  near_ = near;
  far_ = far;
  screenDist_ = screenDist;
  screenHalfHeight_ = 0.5f * screenHeight;
  interOcularHalfDist_ = 0.5f * interOcularDist;
  updateProjection();
}


void StereoCamera::initBourke(GLfloat fovyDeg, GLfloat near, GLfloat far,
    GLfloat screenDist, GLfloat interOcularFactor) {
  near_ = near;
  far_ = far;
  screenDist_ = screenDist;
  interOcularHalfDist_ = 0.5f * interOcularFactor * screenDist_;
  screenHalfHeight_ = screenDist_ * tan(0.5f * glm::radians(fovyDeg));
  updateProjection();
}


const glm::mat4& StereoCamera::getProjection() {
  GLfloat eyeShift = eyeFactor_ * interOcularHalfDist_;   // equals -o_x
  GLfloat factorZ = near_ / screenDist_;
  projection_ = glm::frustum(
      (-eyeShift - screenHalfWidth_) * factorZ, (-eyeShift + screenHalfWidth_) * factorZ,
      -screenHalfHeight_ * factorZ, screenHalfHeight_ * factorZ,
      near_, far_);
  return projection_;
}


const glm::mat4& StereoCamera::getViewTransform(RenderState* renderState) {
  GLfloat eyeShift = eyeFactor_ * interOcularHalfDist_;
  glm::vec3 rightDir = orientation_ * glm::vec3(1.f, 0.f, 0.f);
  viewTransform_ = glm::inverse(renderState->modelViewStack.getMatrix()
      * glm::translate(glm::mat4(1.0f), eyeShift * rightDir));
  return viewTransform_;
}


void StereoCamera::updateProjection() {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  GLfloat aspect = static_cast<GLfloat> (viewport[2] - viewport[0])
      / static_cast<GLfloat> (viewport[3] - viewport[1]);
  screenHalfWidth_ = aspect * screenHalfHeight_;
}


void StereoCamera::render(RenderState* renderState) {
  Camera::render(renderState);
  eyeFactor_ *= -1;
}


} /* namespace scg */
