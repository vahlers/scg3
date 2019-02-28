/**
 * \file Camera.cpp
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

#include "Camera.h"
#include "GeometryCore.h"
#include "GeometryCoreFactory.h"
#include "RenderState.h"
#include "ShaderCore.h"
#include "ShaderCoreFactory.h"
#include "Traverser.h"

namespace scg {


Camera::Camera()
    : projection_(1.0f), viewTransform_(1.0f), eyePt_(0.0f), centerDist_(1.0f),
      orientation_(1.0f, glm::vec3(0.0f)), isDrawCenter_(false) {
  // initialize direction vectors (viewDir_, upDir_, rightDir_, centerPt_) and transformation matrix (matrix_)
  update_();

  // create coordinate axes
  ShaderCoreFactory shaderFactory;
  cores_.push_back(shaderFactory.createColorShader());    // cores_[0]: color shader
  GeometryCoreFactory geometryFactory;
  cores_.push_back(geometryFactory.createXYZAxes(0.1f));  // cores_[1]: center point geometry
}


Camera::~Camera() {
}


const glm::mat4& Camera::getProjection() {
  return projection_;
}


const glm::mat4& Camera::getViewTransform(RenderState* renderState) {
  viewTransform_ = glm::inverse(renderState->modelViewStack.getMatrix());
  return viewTransform_;
}


const glm::vec3& Camera::getPosition() const {
  return eyePt_;
}


Camera* Camera::setPosition(const glm::vec3& position) {
  eyePt_ = position;
  update_();
  return this;
}


const glm::quat& Camera::getOrientation() const {
  return orientation_;
}


Camera* Camera::setOrientation(const glm::quat& orientation) {
  orientation_ = orientation;
  update_();
  return this;
}


const glm::vec3& Camera::getViewDirection() const {
  static glm::vec3 viewDir = glm::vec3(0.0f, 0.0f, -1.0f);
  viewDir = orientation_ * glm::vec3(0.0f, 0.0f, -1.0f);
  return viewDir;
}


GLfloat Camera::getCenterDist() const {
  return centerDist_;
}


Camera* Camera::setMatrix(const glm::mat4& matrix) {
  matrix_ = matrix;
  orientation_ = glm::quat(matrix_);
  eyePt_ = glm::vec3(matrix_[3]);
  update_();
  return this;
}


Camera* Camera::translate(glm::vec3 translation) {
  eyePt_ += orientation_ * translation;
  update_();
  return this;
}


Camera* Camera::rotateRad(GLfloat angleRad, glm::vec3 axis) {
  glm::quat rotation = glm::rotate(glm::quat(1.f, glm::vec3(0.f)), angleRad, axis);
  orientation_ = rotation * orientation_;
  update_();
  return this;
}


Camera* Camera::scale(glm::vec3 scaling) {
  // do nothing
  return this;
}


Camera* Camera::dolly(GLfloat distance) {
  centerDist_ = std::max(0.f, centerDist_ - distance);
  eyePt_ = centerPt_ - centerDist_ * viewDir_;
  update_();
  return this;
}


Camera* Camera::rotateAzimuthRad(GLfloat angleRad) {
  glm::quat rotation = glm::rotate(glm::quat(1.f, glm::vec3(0.f)), angleRad, upDir_);
  viewDir_ = rotation * viewDir_;
  eyePt_ = centerPt_ - centerDist_ * viewDir_;
  orientation_ = rotation * orientation_;
  update_();
  return this;
}


Camera* Camera::rotateElevationRad(GLfloat angleRad) {
  glm::quat rotation = glm::rotate(glm::quat(1.f, glm::vec3(0.f)), -angleRad, rightDir_);
  viewDir_ = rotation * viewDir_;
  eyePt_ = centerPt_ - centerDist_ * viewDir_;
  orientation_ = rotation * orientation_;
  update_();
  return this;
}


Camera* Camera::rotatePitchRad(GLfloat angleRad) {
  glm::quat rotation = glm::rotate(glm::quat(1.f, glm::vec3(0.f)), angleRad, rightDir_);
  orientation_ = rotation * orientation_;
  update_();
  return this;
}


Camera* Camera::rotateRollRad(GLfloat angleRad) {
  glm::quat rotation = glm::rotate(glm::quat(1.f, glm::vec3(0.f)), angleRad, viewDir_);
  orientation_ = rotation * orientation_;
  update_();
  return this;
}


Camera* Camera::rotateYawRad(GLfloat angleRad) {
  glm::quat rotation = glm::rotate(glm::quat(1.f, glm::vec3(0.f)), angleRad, upDir_);
  orientation_ = rotation * orientation_;
  update_();
  return this;
}


bool Camera::isDrawCenter() const {
  return isDrawCenter_;
}


Camera* Camera::setDrawCenter(bool isDrawCenter) {
  isDrawCenter_ = isDrawCenter;
  return this;
}


void Camera::accept(Traverser* traverser) {
  traverser->visitCamera(this);
}


void Camera::acceptPost(Traverser *traverser) {
  traverser->visitPostCamera(this);
}


void Camera::render(RenderState* renderState) {
  Transformation::render(renderState);

  // if enabled, render xyz coordinate axes at center point
  if (isDrawCenter_) {
    assert(cores_.size() >= 2);
    assert(std::dynamic_pointer_cast<ShaderCore>(cores_[0]));
    cores_[0]->render(renderState);       // color shader
    renderState->modelViewStack.pushMatrix();
    renderState->modelViewStack.setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -centerDist_)));
    renderState->modelViewStack.multMatrix(glm::mat4_cast(glm::inverse(orientation_)));
    assert(std::dynamic_pointer_cast<GeometryCore>(cores_[1]));
    cores_[1]->render(renderState);       // center point geometry
    renderState->modelViewStack.popMatrix();
    // restore shader
    cores_[0]->renderPost(renderState);   // restore previous shader
  }
}


void Camera::renderPost(RenderState* renderState) {
  Transformation::renderPost(renderState);
}


void Camera::update_() {
  // rotate direction vectors by current orientation quaternion
  viewDir_ = orientation_ * glm::vec3(0.0f, 0.0f, -1.0f);
  upDir_ = orientation_ * glm::vec3(0.0f, 1.0f, 0.0f);
  rightDir_ = glm::cross(viewDir_, upDir_);

  // set current center point
  centerPt_ = eyePt_ + centerDist_ * viewDir_;

  // update transformation matrix and camera
  matrix_ = glm::mat4(glm::vec4(rightDir_, 0.f), glm::vec4(upDir_, 0.f),
      glm::vec4(-viewDir_, 0.f), glm::vec4(eyePt_, 1.f));
}


} /* namespace scg */
