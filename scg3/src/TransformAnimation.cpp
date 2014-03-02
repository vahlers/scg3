/**
 * \file TransformAnimation.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
