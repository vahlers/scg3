/**
 * \file PerspectiveCamera.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "PerspectiveCamera.h"
#include "scg_glm.h"

namespace scg {


PerspectiveCamera::PerspectiveCamera()
    : fovyDeg_(60.f), near_(0.01f), far_(1000.f) {
}


PerspectiveCamera::~PerspectiveCamera() {
}


PerspectiveCameraSP PerspectiveCamera::create() {
  return std::make_shared<PerspectiveCamera>();
}


void PerspectiveCamera::init(float fovyDeg, float near, float far) {
  fovyDeg_ = fovyDeg;
  near_ = near;
  far_ = far;
  updateProjection();
}


void PerspectiveCamera::updateProjection() {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  GLfloat aspect = static_cast<GLfloat> (viewport[2] - viewport[0])
      / static_cast<GLfloat> (viewport[3] - viewport[1]);
  projection_ = glm::perspective(fovyDeg_, aspect, near_, far_);
}


} /* namespace scg */
