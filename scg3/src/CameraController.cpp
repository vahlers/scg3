/**
 * \file CameraController.cpp
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
