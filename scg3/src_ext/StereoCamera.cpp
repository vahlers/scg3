/**
 * \file StereoCamera.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "../src/RenderState.h"
#include "StereoCamera.h"

namespace scg {

StereoCamera::StereoCamera()
    : eyeFactor_(-1) {
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
      * glm::translate(glm::mat4(), eyeShift * rightDir));
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
