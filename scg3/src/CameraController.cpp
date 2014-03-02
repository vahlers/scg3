/**
 * \file CameraController.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include "Camera.h"
#include "CameraController.h"

namespace scg {


CameraController::CameraController(CameraSP camera)
    : camera_(camera), moveVelocity_(0.f), rotateVelocity_(0.f),
      flightVelocity_(0.f), flightVelocityStep_(0.f), isFlyMode_(true) {
}


CameraController::~CameraController() {
}


void CameraController::setCamera(CameraSP camera) {
  camera_ = camera;
}


void CameraController::setMoveVelocity(GLfloat moveVelocity) {
  moveVelocity_ = moveVelocity;
}


void CameraController::setRotateVelocity(GLfloat rotateVelocity) {
  rotateVelocity_ = rotateVelocity;
}


void CameraController::setFlightVelocity(GLfloat flightVelocity) {
  flightVelocity_ = flightVelocity;
}


void CameraController::setFlightVelocityStep(GLfloat flightVelocityStep) {
  flightVelocityStep_ = flightVelocityStep;
}


} /* namespace scg */
