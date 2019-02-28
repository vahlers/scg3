/**
 * \file PerspectiveCamera.cpp
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

#include "PerspectiveCamera.h"
#include "scg_glm.h"

namespace scg {


PerspectiveCamera::PerspectiveCamera()
    : fovyRad_(glm::radians(60.0f)), near_(0.01f), far_(1000.f) {
}


PerspectiveCamera::~PerspectiveCamera() {
}


PerspectiveCameraSP PerspectiveCamera::create() {
  return std::make_shared<PerspectiveCamera>();
}


void PerspectiveCamera::init(float fovyDeg, float near, float far) {
  fovyRad_ = glm::radians(fovyDeg);
  near_ = near;
  far_ = far;
  updateProjection();
}


void PerspectiveCamera::updateProjection() {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  GLfloat aspect = static_cast<GLfloat> (viewport[2] - viewport[0])
      / static_cast<GLfloat> (viewport[3] - viewport[1]);
  projection_ = glm::perspective(fovyRad_, aspect, near_, far_);
}


} /* namespace scg */
