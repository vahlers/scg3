/**
 * \file OrthographicCamera.cpp
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

#include "scg_glm.h"
#include "OrthographicCamera.h"

namespace scg {


OrthographicCamera::OrthographicCamera()
    : left_(-1.f), right_(1.f), bottom_(-1.f), top_(1.f), near_(-1.f), far_(1.f) {
}


OrthographicCamera::~OrthographicCamera() {
}


OrthographicCameraSP OrthographicCamera::create() {
  return std::make_shared<OrthographicCamera>();
}


void OrthographicCamera::init(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top,
    GLfloat near, GLfloat far) {
  left_ = left;
  right_ = right;
  bottom_ = bottom;
  top_ = top;
  near_ = near;
  far_ = far;
  updateProjection();
}


void OrthographicCamera::updateProjection() {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  GLfloat aspect = static_cast<GLfloat> (viewport[2] - viewport[0])
      / static_cast<GLfloat> (viewport[3] - viewport[1]);
  GLfloat halfWidth = 0.5f * aspect * (top_ - bottom_);
  GLfloat horizCenter = 0.5f * (left_ + right_);
  projection_ = glm::ortho(horizCenter - halfWidth, horizCenter + halfWidth,
      bottom_, top_, near_, far_);
}


} /* namespace scg */
