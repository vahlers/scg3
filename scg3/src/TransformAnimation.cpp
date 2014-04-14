/**
 * \file TransformAnimation.cpp
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

#include "TransformAnimation.h"

namespace scg {


TransformAnimation::TransformAnimation() {
}


TransformAnimation::~TransformAnimation() {
}


TransformAnimationSP TransformAnimation::create() {
  return std::make_shared<TransformAnimation>();
}


GLfloat TransformAnimation::getFloatParam() const {
  return floatParam_;
}


TransformAnimation* TransformAnimation::setFloatParam(GLfloat param) {
  floatParam_ = param;
  return this;
}


const glm::vec3& TransformAnimation::getVec3Param() const {
  return vec3Param_;
}


TransformAnimation* TransformAnimation::setVec3Param(const glm::vec3& param) {
  vec3Param_ = param;
  return this;
}


const glm::mat4& TransformAnimation::getMat4Param() const {
  return mat4Param_;
}


TransformAnimation* TransformAnimation::setMat4Param(const glm::mat4& param) {
  mat4Param_ = param;
  return this;
}


TransformAnimation* TransformAnimation::setStartFunc(std::function<void(TransformAnimation*)> startFunc) {
  startFunc_ = startFunc;
  return this;
}


TransformAnimation* TransformAnimation::setUpdateFunc(std::function<void(TransformAnimation*, double, double, double)> updateFunc) {
  updateFunc_ = updateFunc;
  return this;
}


void TransformAnimation::start(double currTime) {
  if (!isStarted_ && startFunc_ != nullptr) {
    startFunc_(this);
  }
  Animation::start(currTime);
}


void TransformAnimation::update(double currTime) {
  if (isRunning_) {
    Animation::update(currTime);
    if (updateFunc_ != nullptr) {
      updateFunc_(this, currTime, diffTime_, totalTime_);
    }
  }
}


} /* namespace scg */
